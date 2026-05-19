// Reads the shield's five-button keypad via the A0 analog resistor ladder and displays which button is currently pressed on the LCD.
//
// Buy this module: https://shillehtek.com/products/shillehtek-lcd1602-16x2-keypad-shield
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lcd1602-16x2-keypad-shield-manual
// More examples: https://github.com/shillehtek/examples
//

// LCD1602 Keypad Shield - Read Buttons via A0 Resistor Ladder
// Prints the active button on the LCD.

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

enum Button { BTN_NONE, BTN_RIGHT, BTN_UP, BTN_DOWN, BTN_LEFT, BTN_SELECT };

Button readButton() {
  int v = analogRead(A0);
  if (v < 50)   return BTN_RIGHT;
  if (v < 150)  return BTN_UP;
  if (v < 300)  return BTN_DOWN;
  if (v < 500)  return BTN_LEFT;
  if (v < 750)  return BTN_SELECT;
  return BTN_NONE;
}

void setup() {
  lcd.begin(16, 2);
  lcd.print("Press a button:");
}

void loop() {
  Button b = readButton();
  lcd.setCursor(0, 1);
  switch (b) {
    case BTN_RIGHT:  lcd.print("RIGHT          "); break;
    case BTN_UP:     lcd.print("UP             "); break;
    case BTN_DOWN:   lcd.print("DOWN           "); break;
    case BTN_LEFT:   lcd.print("LEFT           "); break;
    case BTN_SELECT: lcd.print("SELECT         "); break;
    default:         lcd.print("(none)         "); break;
  }
  delay(100);
}
