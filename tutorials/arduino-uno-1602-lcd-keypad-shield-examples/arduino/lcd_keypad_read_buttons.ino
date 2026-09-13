// Reads the analog input from the LCD keypad shield and displays which button (Right, Up, Down, Left, Select) is pressed on the 16x2 LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-1602-lcd-keypad-shield-examples
// Parts used: https://shillehtek.com/products/shillehtek-lcd1602-16x2-keypad-shield
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal.h>

// LCD pin assignments matching the shield
const int pin_RS = 8;
const int pin_EN = 9;
const int pin_d4 = 4;
const int pin_d5 = 5;
const int pin_d6 = 6;
const int pin_d7 = 7;
const int pin_BL = 10;

LiquidCrystal lcd(pin_RS, pin_EN, pin_d4, pin_d5, pin_d6, pin_d7);

void setup() {
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("ShillehTek.com");
  lcd.setCursor(0, 1);
  lcd.print("Press Key:");
}

void loop() {
  int x;
  x = analogRead(0);
  lcd.setCursor(10, 1);
  if (x < 60) {
    lcd.print("Right ");
  } else if (x < 200) {
    lcd.print("Up    ");
  } else if (x < 400) {
    lcd.print("Down  ");
  } else if (x < 600) {
    lcd.print("Left  ");
  } else if (x < 800) {
    lcd.print("Select");
  }
}
