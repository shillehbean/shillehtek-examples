// Initializes the 16x2 LCD and prints a two-line 'hello world' message prompting the user to press a button.
//
// Buy this module: https://shillehtek.com/products/shillehtek-lcd1602-16x2-keypad-shield
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lcd1602-16x2-keypad-shield-manual
// More examples: https://github.com/shillehtek/examples
//

// LCD1602 Keypad Shield - Hello World
// Uses the standard LiquidCrystal library.
// LCD pins: RS=8, E=9, D4=4, D5=5, D6=6, D7=7

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("ShillehTek LCD");
  lcd.setCursor(0, 1);
  lcd.print("Press a button");
}

void loop() {
  // Nothing to do — second example handles input
}
