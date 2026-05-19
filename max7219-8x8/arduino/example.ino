// Uses the LedControl Arduino library to drive a single MAX7219 8x8 matrix, draw a smiley face, set brightness, and blink the display on and off.
//
// Buy this module: https://shillehtek.com/products/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// MAX7219 8x8 - Display a smiley face
// Library: LedControl by Eberhard Fahle (Library Manager)

#include <LedControl.h>

// Args: DIN pin, CLK pin, CS pin, number of cascaded modules
LedControl lc = LedControl(11, 13, 10, 1);

byte smiley[8] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

void setup() {
  lc.shutdown(0, false);     // Wake up the display
  lc.setIntensity(0, 8);     // Brightness 0-15
  lc.clearDisplay(0);
}

void loop() {
  for (int row = 0; row < 8; row++) {
    lc.setRow(0, row, smiley[row]);
  }
  delay(2000);
  lc.clearDisplay(0);
  delay(500);
}
