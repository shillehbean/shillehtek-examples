// Provides a simple menu skeleton that lets the user move a cursor with UP/DOWN and trigger an action with SELECT using the keypad read from A0.
//
// Buy this module: https://shillehtek.com/products/shillehtek-lcd1602-16x2-keypad-shield
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lcd1602-16x2-keypad-shield-manual
// More examples: https://github.com/shillehtek/examples
//

// LCD1602 Keypad Shield - Simple Menu Skeleton
// UP/DOWN moves the cursor, SELECT triggers the action.

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const char* items[] = {"Start", "Settings", "About"};
const int itemCount = 3;
int cursor = 0;
unsigned long lastInput = 0;

int readButton() {
  int v = analogRead(A0);
  if (v < 50)   return 1;  // RIGHT
  if (v < 150)  return 2;  // UP
  if (v < 300)  return 3;  // DOWN
  if (v < 500)  return 4;  // LEFT
  if (v < 750)  return 5;  // SELECT
  return 0;
}

void drawMenu() {
  lcd.clear();
  lcd.print("Menu:");
  lcd.setCursor(0, 1);
  lcd.print("> ");
  lcd.print(items[cursor]);
}

void setup() {
  lcd.begin(16, 2);
  drawMenu();
}

void loop() {
  int b = readButton();
  if (b && millis() - lastInput > 200) {
    lastInput = millis();
    if (b == 2 && cursor > 0)              cursor--;
    if (b == 3 && cursor < itemCount - 1) cursor++;
    if (b == 5) {
      lcd.clear();
      lcd.print("Selected:");
      lcd.setCursor(0, 1);
      lcd.print(items[cursor]);
      delay(1500);
    }
    drawMenu();
  }
}
