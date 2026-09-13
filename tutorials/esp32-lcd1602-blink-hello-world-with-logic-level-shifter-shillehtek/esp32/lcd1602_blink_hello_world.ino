// Blink a "Hello, World!" message on a 16x2 LCD using the LiquidCrystal library and direct GPIO pins on an ESP32.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-lcd1602-blink-hello-world-with-logic-level-shifter-shillehtek
// Parts used: https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered
//             https://shillehtek.com/products/shillehtek-400-point-breadboard
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(13, 14, 27, 26, 25, 33);

const unsigned long BLINK_MS = 1000; // 1000 = 1 second

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // ON
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  delay(BLINK_MS);

  // OFF
  lcd.clear();
  delay(BLINK_MS);
}
