// Implements IMU reading with a complementary filter, declares OLED and game state, and begins target generation for the tilt game.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mpu6050-tilt-game-oled-level
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int MPU = 0x68, BTN = 7, BUZZ = 8;
float pitch = 0, roll = 0;
unsigned long lastUs = 0;

// ---- sensor fusion ----
void readIMU() {
  Wire.beginTransmission(MPU); Wire.write(0x3B); Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  int16_t ax = Wire.read() << 8 | Wire.read(), ay = Wire.read() << 8 | Wire.read(), az = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();                                        // skip temperature
  int16_t gx = Wire.read() << 8 | Wire.read(), gy = Wire.read() << 8 | Wire.read(); Wire.read(); Wire.read();

  float accPitch = atan2(ay, az) * 57.3;                           // degrees from gravity
  float accRoll  = atan2(-ax, az) * 57.3;
  unsigned long now = micros(); float dt = (now - lastUs) / 1e6; lastUs = now;
  pitch = 0.98 * (pitch + gx / 131.0 * dt) + 0.02 * accPitch;      // complementary filter
  roll  = 0.98 * (roll  + gy / 131.0 * dt) + 0.02 * accRoll;
}

// ---- game state ----
float bx = 64, by = 32; int tx, ty, score; unsigned long gameEnd;
void newTarget() { tx = random(8, 120); ty = random(8, 56); }

void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU); Wire.write(0x6B); Wire.write(0); Wire.endTransmission();   // wake up
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); oled.setTextColor(SSD1306_WHITE);
  pinMode(BTN, INPUT_PULLUP);
  randomSeed(analogRead(A0));
  lastUs = micros(); newTarget(); gameEnd = millis() + 60000;
}

void loop() {
  readIMU();
  oled.clearDisplay();

  if (digitalRead(BTN) == LOW) {                                   // ---- LEVEL MODE ----
    int cx = 64 + constrain(roll, -30, 30) * 2, cy = 32 + constrain(pitch, -30, 30) * 1;
    oled.drawCircle(64, 32, 20, SSD1306_WHITE); oled.drawCircle(64, 32, 3, SSD1306_WHITE);
    oled.fillCircle(cx, cy, 4, SSD1306_WHITE);                     // the bubble
    oled.setTextSize(1);
    oled.setCursor(0, 0);  oled.print("P "); oled.print(pitch, 1);
    oled.setCursor(0, 56); oled.print("R "); oled.print(roll, 1);
    if (abs(pitch) < 0.5 && abs(roll) < 0.5) { oled.setCursor(92, 0); oled.print("LEVEL"); }
  } else {                                                         // ---- GAME MODE ----
    bx = constrain(bx + roll * 0.08, 2, 125);                      // tilt = velocity
    by = constrain(by + pitch * 0.08, 2, 61);
    if (abs(bx - tx) < 5 && abs(by - ty) < 5) { score++; tone(BUZZ, 1200, 60); newTarget(); }
    long left = (gameEnd - millis()) / 1000;
    if (left <= 0) {                                               // time's up
      oled.setTextSize(2); oled.setCursor(16, 20); oled.print("SCORE "); oled.print(score);
      oled.display(); tone(BUZZ, 300, 500); delay(3000);
      score = 0; bx = 64; by = 32; gameEnd = millis() + 60000; return;
    }
    oled.drawRect(tx - 3, ty - 3, 7, 7, SSD1306_WHITE);            // target
    oled.fillCircle((int)bx, (int)by, 3, SSD1306_WHITE);           // ball
    oled.setTextSize(1); oled.setCursor(0, 0); oled.print(score);
    oled.setCursor(110, 0); oled.print(left);
  }
  oled.display();
}
