// ESP32 Arduino sketch using LiquidCrystal in 4-bit mode (RW tied to GND) to display static text and an incrementing counter.
//
// Buy this module: https://shillehtek.com/products/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/lcd2004-20x4-blue-backlight-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// LCD2004 20x4 Character LCD - ESP32 Example (4-bit mode)
// RS->13, E->12, D4->14, D5->27, D6->26, D7->25, RW->GND, VDD->5V

#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 14, 27, 26, 25);
unsigned long count = 0;

void setup() {
  lcd.begin(20, 4);
  lcd.setCursor(0, 0);
  lcd.print("ESP32 + LCD2004");
  lcd.setCursor(0, 1);
  lcd.print("Write-only is safe:");
  lcd.setCursor(0, 2);
  lcd.print("RW tied to GND");
}

void loop() {
  lcd.setCursor(0, 3);
  lcd.print("Count: ");
  lcd.print(count++);
  lcd.print("   ");
  delay(1000);
}
