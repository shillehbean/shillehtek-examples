// Arduino sketch using the LiquidCrystal library in 4-bit mode to initialize a 20x4 LCD, print static lines, and update a seconds uptime counter.
//
// Buy this module: https://shillehtek.com/products/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// LCD2004 20x4 Character LCD - Arduino Example (4-bit mode)
// RS->12, E->11, D4->5, D5->4, D6->3, D7->2, RW->GND

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);   // RS, E, D4, D5, D6, D7
unsigned long count = 0;

void setup() {
  lcd.begin(20, 4);                      // 20 columns, 4 rows
  lcd.setCursor(0, 0);
  lcd.print("ShillehTek LCD2004");
  lcd.setCursor(0, 1);
  lcd.print("20 x 4 characters");
  lcd.setCursor(0, 2);
  lcd.print("HD44780 4-bit mode");
}

void loop() {
  lcd.setCursor(0, 3);
  lcd.print("Uptime: ");
  lcd.print(count++);
  lcd.print(" s   ");
  delay(1000);
}
