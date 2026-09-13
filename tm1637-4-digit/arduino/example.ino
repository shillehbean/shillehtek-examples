// Basic Arduino example that counts 0–9999 on the TM1637 display and then shows a colon clock pattern (12:34) for a few seconds.
//
// Buy this module: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-bits-tm1637-red-led-display-module-clock-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TM1637 4-Digit Display - Arduino Example (Counter + Clock)
// Requires: TM1637 library by Avishay Orpaz (Library Manager)

#include <TM1637Display.h>

const int CLK = 2;
const int DIO = 3;

TM1637Display display(CLK, DIO);

void setup() {
  display.setBrightness(5);   // 0 = dim, 7 = max
  display.clear();
}

void loop() {
  // Count 0 - 9999 over and over
  for (int i = 0; i < 10000; i++) {
    display.showNumberDec(i, true);   // true = leading zeros
    delay(100);
  }

  // Show a colon clock for 5 seconds (12:34)
  display.showNumberDecEx(1234, 0x40, true);
  delay(5000);
}
