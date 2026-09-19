// Arduino sketch that reads GSR on A0, computes fast and slow filtered values to detect conductance changes, displays a needle-style meter on an SSD1306 OLED, prints telemetry over Serial, and controls a buzzer for alerts.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-gsr-oled-meter
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 oled(128, 64, &Wire, -1);
const int GSR = A0, BUZZ = 8;
const float ALERT = 25;              // deviation (ADC counts) that counts as a reaction
float fast = 0, slow = 0;            // fast-following value and slow-moving baseline

void setup() {
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextColor(SSD1306_WHITE);
  slow = fast = analogRead(GSR);
}

void loop() {
  int raw = 0;
  for (int i = 0; i < 16; i++) raw += analogRead(GSR);   // average away noise
  raw /= 16;

  fast = 0.8 * fast + 0.2 * raw;      // responds in ~1 s
  slow = 0.995 * slow + 0.005 * raw;  // drifts over ~30 s: the "resting" level
  float dev = fast - slow;            // positive = conductance rose = reaction

  Serial.print(raw); Serial.print(" "); Serial.print(slow); Serial.print(" "); Serial.println(dev);

  // needle: center = no change, right = reaction, left = relaxing
  int needle = constrain(64 + dev * 2, 4, 124);
  oled.clearDisplay();
  oled.drawRect(4, 20, 120, 24, SSD1306_WHITE);
  oled.drawFastVLine(64, 16, 32, SSD1306_WHITE);            // center mark
  oled.fillRect(min(64, needle), 24, abs(needle - 64), 16, SSD1306_WHITE);
  oled.setTextSize(1);
  oled.setCursor(0, 0);  oled.print(raw < 20 ? "hold both electrodes" : "GSR meter");
  oled.setCursor(0, 54); oled.print("dev "); oled.print(dev, 1);
  if (dev > ALERT && raw > 20) { oled.setCursor(80, 54); oled.print("REACT!"); tone(BUZZ, 1500, 80); }
  oled.display();
  delay(50);
}
