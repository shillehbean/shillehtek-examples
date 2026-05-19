// Initializes the SH1106 over hardware I2C using the U8g2 library and draws static text lines on the 128x64 display.
//
// Buy this module: https://shillehtek.com/products/1-3-i2c-white-oled-display-module-4-pin-sh1106
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-3-i2c-white-oled-display-module-4-pin-sh1106-manual
// More examples: https://github.com/shillehtek/examples
//

// 1.3" SH1106 OLED - Arduino I2C Example
// Library: U8g2 by olikraus (Library Manager) - the recommended driver for SH1106
// Wiring: SDA -> A4, SCL -> A5

#include <U8g2lib.h>
#include <Wire.h>

// Hardware I2C constructor for 1.3" SH1106 128x64
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  display.begin();
  display.setContrast(255);

  display.clearBuffer();
  display.setFont(u8g2_font_ncenB14_tr);
  display.drawStr(0, 20, "ShillehTek");
  display.setFont(u8g2_font_6x10_tr);
  display.drawStr(0, 40, "SH1106 OLED 1.3\"");
  display.drawStr(0, 55, "128 x 64 I2C");
  display.sendBuffer();
}

void loop() {
  // Static demo - nothing to update
}
