// Initializes an SSD1306 128x32 I2C OLED with U8g2 and displays two lines of text repeatedly.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-ssd1306-oled-display-text
// Parts used: https://shillehtek.com/products/oled-ssd1306-128x32-i2c-0-91in
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <U8g2lib.h>
#include <Wire.h>

// SSD1306 128x32, hardware I2C
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

void setup() {
  u8g2.begin();
}

void loop() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0, 12, "Hello from the");
  u8g2.drawStr(0, 28, "0.91in 128x32 OLED");
  u8g2.sendBuffer();
  delay(1000);
}
