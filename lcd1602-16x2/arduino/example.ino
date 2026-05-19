// Initializes the LCD in 4-bit mode with the LiquidCrystal library, prints static messages and updates an uptime seconds counter on the second row every second.
//
// Buy this module: https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-lcd1602-16x2-character-display-module-manual
// More examples: https://github.com/shillehtek/examples
//

// LCD1602 16x2 LCD Display - Arduino Example
// 4-bit mode using LiquidCrystal library
// RS = 12, E = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2

#include <LiquidCrystal.h>

// (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // Tell the LCD it has 16 columns and 2 rows
  lcd.begin(16, 2);
  lcd.print("Hello, World!");

  lcd.setCursor(0, 1);
  lcd.print("ShillehTek LCD");
}

void loop() {
  // Move the cursor and print the seconds counter on row 2
  lcd.setCursor(0, 1);
  lcd.print("Uptime: ");
  lcd.print(millis() / 1000);
  lcd.print("s   ");
  delay(1000);
}
