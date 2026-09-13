// Sketch that accumulates total liters over time, calculates L/min, and updates a 16x2 LCD with current flow and total volume (assumes an initialized lcd object).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-yf-s201-water-flow-measure-lpm
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

float total_liters = 0.0;
void loop() {
  unsigned long p = pulses;
  pulses = 0;
  delay(1000);
  float lpm = (p * 60.0) / 450.0;
  total_liters += lpm / 60.0;   // 1 second of flow

  lcd.setCursor(0, 0);
  lcd.print(lpm, 1); lcd.print(" L/min ");
  lcd.setCursor(0, 1);
  lcd.print("Total "); lcd.print(total_liters, 2); lcd.print(" L");
}
