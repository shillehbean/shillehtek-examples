// Initializes a 20x4 I2C LCD and displays four lines of text.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-lcd2004-i2c-hello-world-display
// Parts used: https://shillehtek.com/products/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // address, columns, rows

void setup() {
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  lcd.setCursor(0, 1);
  lcd.print("LCD2004 over I2C");
  lcd.setCursor(0, 2);
  lcd.print("4 lines x 20 chars");
  lcd.setCursor(0, 3);
  lcd.print("Only 4 wires needed");
}

void loop() {
}
