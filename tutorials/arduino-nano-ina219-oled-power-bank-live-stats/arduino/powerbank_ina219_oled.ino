// Reads voltage, current, and power from an INA219 sensor and displays the values on a 128x64 SSD1306 OLED, updating every 500 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ina219-oled-power-bank-live-stats
// Parts used: https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection
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
  oled.setTextColor(SSD1306_WHITE); oled.setTextSize(1);
}
void loop() {
  float v = ina.getBusVoltage_V(), mA = ina.getCurrent_mA(), mW = ina.getPower_mW();
  oled.clearDisplay(); oled.setCursor(0, 0);
  oled.printf("V: %.2f V\nI: %.0f mA\nP: %.0f mW\n", v, mA, mW);
  oled.display();
  delay(500);
}
