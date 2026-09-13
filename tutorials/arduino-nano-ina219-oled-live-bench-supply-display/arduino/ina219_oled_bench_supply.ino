// Reads bus voltage, current, and power from an INA219 sensor and displays the values on an SSD1306 OLED, updating approx. every 250 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ina219-oled-live-bench-supply-display
// Parts used: https://shillehtek.com/products/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module
//             https://shillehtek.com/products/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_INA219 ina;
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
void setup() {
  ina.begin();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}
void loop() {
  float v = ina.getBusVoltage_V();
  float mA = ina.getCurrent_mA();
  float mW = ina.getPower_mW();
  oled.clearDisplay(); oled.setTextColor(SSD1306_WHITE);
  oled.setTextSize(2); oled.setCursor(0, 0);
  oled.print(v, 2); oled.println(" V");
  oled.setTextSize(1);
  oled.print(mA, 0); oled.println(" mA");
  oled.print(mW, 0); oled.println(" mW");
  oled.display();
  delay(250);
}
