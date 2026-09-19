// Arduino sketch that implements a two-player Pong game on a 0.96" SSD1306 I2C OLED, reading two potentiometers for paddles and using a buzzer for sound effects.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ssd1306-oled-pong-game
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int POT_L = A0, POT_R = A1, BUZZ = 8;
const int PADDLE_H = 14, PADDLE_W = 3, WIN = 8;
float bx = 64, by = 32, vx = 1.6, vy = 1.0;     // ball position and velocity (pixels/frame)
int scoreL = 0, scoreR = 0;

void beep(int f) { tone(BUZZ, f, 30); }

void resetBall(int dir) {                       // serve toward the player who just scored
  bx = 64; by = random(10, 54);
  vx = 1.6 * dir; vy = random(-10, 11) / 10.0;
}

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  randomSeed(analogRead(A3));
  resetBall(1);
}

void loop() {
  int pl = map(analogRead(POT_L), 0, 1023, 0, 64 - PADDLE_H);   // paddle top edges
  int pr = map(analogRead(POT_R), 0, 1023, 0, 64 - PADDLE_H);

  bx += vx; by += vy;
  if (by <= 0 || by >= 63) { vy = -vy; beep(400); }             // top / bottom walls

  // paddle hits: reverse, speed up 5%, add spin from where it struck the paddle
  if (bx <= 5 && by >= pl && by <= pl + PADDLE_H) {
    vx = -vx * 1.05; vy += (by - (pl + PADDLE_H / 2)) / 8.0; beep(800);
  }
  if (bx >= 122 && by >= pr && by <= pr + PADDLE_H) {
    vx = -vx * 1.05; vy += (by - (pr + PADDLE_H / 2)) / 8.0; beep(800);
  }
  vy = constrain(vy, -2.5, 2.5);

  if (bx < 0)   { scoreR++; beep(150); resetBall(1);  }         // missed on the left
  if (bx > 127) { scoreL++; beep(150); resetBall(-1); }         // missed on the right

  oled.clearDisplay();
  oled.fillRect(2,   pl, PADDLE_W, PADDLE_H, SSD1306_WHITE);
  oled.fillRect(123, pr, PADDLE_W, PADDLE_H, SSD1306_WHITE);
  oled.fillRect((int)bx, (int)by, 2, 2, SSD1306_WHITE);
  for (int y = 0; y < 64; y += 6) oled.drawFastVLine(64, y, 3, SSD1306_WHITE);   // the net
  oled.setTextSize(1);
  oled.setCursor(50, 2); oled.print(scoreL);
  oled.setCursor(72, 2); oled.print(scoreR);
  oled.display();

  if (scoreL >= WIN || scoreR >= WIN) {
    oled.clearDisplay(); oled.setTextSize(2); oled.setCursor(4, 24);
    oled.print(scoreL >= WIN ? "LEFT WINS" : "RIGHT WINS");
    oled.display(); delay(3000);
    scoreL = scoreR = 0; resetBall(1);
  }
}
