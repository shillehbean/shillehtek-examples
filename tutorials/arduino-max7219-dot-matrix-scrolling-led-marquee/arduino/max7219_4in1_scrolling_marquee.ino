// Configure four chained MAX7219 8x8 modules (32×8) and scroll the message "ShillehTek - IoT for Builders" from right to left using MD_Parola animations.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-max7219-dot-matrix-scrolling-led-marquee
// Parts used: https://shillehtek.com/products/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino
//             https://shillehtek.com/products/max7219-4-in-1-dot-matrix-display-module-red
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4     // 4-in-1 module = 32×8 surface
#define CS_PIN 10

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(3);
  display.displayClear();
  display.displayScroll("ShillehTek - IoT for Builders",
                        PA_LEFT, PA_SCROLL_LEFT, 75);
}

void loop() {
  if (display.displayAnimate()) display.displayReset();
}
