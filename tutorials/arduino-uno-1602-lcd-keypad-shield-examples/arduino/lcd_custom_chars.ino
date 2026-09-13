// Defines several custom 5x8 characters (smiley, battery, arrows, ohm, heart) and writes them to the LCD to show how to render custom glyphs.
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

// Smiley face
byte smiley[8] = {
  B00000, B10001, B00000, B00000,
  B10001, B01110, B00000,
};

// Battery icon
byte battery[] = {
  B01110, B01010, B11011, B10001,
  B11111, B11111, B11111, B11111
};

// Right arrow
byte R_arrow[8] = {
  B00000, B00100, B00010, B11111,
  B00010, B00100, B00000, B00000
};

// Left arrow
byte L_arrow[8] = {
  B00000, B00100, B01000, B11111,
  B01000, B00100, B00000, B00000
};

// Ohm symbol
byte ohm[8] = {
  B00000, B01110, B10001, B10001,
  B10001, B01010, B11011, B00000
};

// Heart
byte heart[8] = {
  B00000, B01010, B10101, B10001,
  B10001, B01010, B00100, B00000
};

void setup() {
  lcd.begin(16, 2);
  lcd.createChar(0, smiley);
  lcd.createChar(1, battery);
  lcd.createChar(2, R_arrow);
  lcd.createChar(3, L_arrow);
  lcd.createChar(4, ohm);
  lcd.createChar(5, heart);

  for (int n = 0; n < 6; n++) {
    lcd.setCursor(n * 2, 0);
    lcd.write(n);
  }
}

void loop() {
}
