// Initializes a 16x2 I2C LCD, creates four custom characters (heart, smiley, bell, degree) and displays them alongside text.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-16x2-lcd-custom-characters-animations
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte heart[8]  = {B00000, B01010, B11111, B11111, B01110, B00100, B00000, B00000};
byte smiley[8] = {B00000, B01010, B01010, B00000, B10001, B01110, B00000, B00000};
byte bell[8]   = {B00100, B01110, B01110, B01110, B11111, B00000, B00100, B00000};
byte degree[8] = {B01100, B10010, B10010, B01100, B00000, B00000, B00000, B00000};

void setup() {
  lcd.init(); lcd.backlight();
  lcd.createChar(0, heart);          // slots 0..7 are yours
  lcd.createChar(1, smiley);
  lcd.createChar(2, bell);
  lcd.createChar(3, degree);
  lcd.setCursor(0, 0);               // always set the cursor after createChar()
  lcd.print("I "); lcd.write(byte(0)); lcd.print(" Arduino "); lcd.write(byte(1));
  lcd.setCursor(0, 1);
  lcd.write(byte(2)); lcd.print(" 23.5"); lcd.write(byte(3)); lcd.print("C");
}

void loop() {}
