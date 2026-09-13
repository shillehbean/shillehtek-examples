// Demonstrates scrolling a text string left and right on the 16x2 LCD using lcd.scrollDisplayLeft() and lcd.scrollDisplayRight().
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-1602-lcd-keypad-shield-examples
// Parts used: https://shillehtek.com/products/shillehtek-lcd1602-16x2-keypad-shield
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal.h>

const int RS = 8;
const int EN = 9;
const int d4 = 4;
const int d5 = 5;
const int d6 = 6;
const int d7 = 7;
const int pin_BL = 10;

LiquidCrystal lcd(RS, EN, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("ShillehTek");
  delay(1000);
}

void loop() {
  // Scroll 10 positions to the left
  for (int i = 0; i < 10; i++) {
    lcd.scrollDisplayLeft();
    delay(400);
  }

  // Scroll 26 positions to the right
  for (int i = 0; i < 26; i++) {
    lcd.scrollDisplayRight();
    delay(400);
  }

  // Scroll 16 positions back to the left quickly
  for (int i = 0; i < 16; i++) {
    lcd.scrollDisplayLeft();
    delay(50);
  }

  delay(1000);
}
