// Scrolls the message "ShillehTek MAX7219" across four cascaded 8x8 matrices using the MD_Parola and MD_MAX72XX libraries on an Arduino (DIN->D11, CS->D10, CLK->D13).
//
// Buy this module: https://shillehtek.com/products/max7219-4-in-1-dot-matrix-display-module-red
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max7219-4-in-1-dot-matrix-display-module-red-manual
// More examples: https://github.com/shillehtek/examples
//

// MAX7219 4-in-1 Dot Matrix - Arduino Scrolling Text
// Library: MD_Parola + MD_MAX72XX (Library Manager)
// Wiring: DIN -> D11, CS -> D10, CLK -> D13

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES   4     // number of 8x8 blocks in the chain
#define CS_PIN        10

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(5);       // 0 (dim) - 15 (bright)
  display.displayClear();
  display.displayScroll("ShillehTek MAX7219", PA_LEFT, PA_SCROLL_LEFT, 80);
}

void loop() {
  if (display.displayAnimate()) {
    display.displayReset();
  }
}
