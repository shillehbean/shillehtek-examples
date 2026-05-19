// Initializes a 16x2 LCD over I2C using the LiquidCrystal_I2C library and displays two lines of text.
//
// Buy this module: https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd-manual
// More examples: https://github.com/shillehtek/examples
//

// PCF8574 I2C 1602 LCD - Arduino Example
// Library: LiquidCrystal_I2C by Frank de Brabander

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set I2C address (0x27 typical, try 0x3F if blank)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Hello, ShillehTek!");
  lcd.setCursor(0, 1);
  lcd.print("PCF8574 I2C LCD");
}

void loop() {
  // nothing
}
