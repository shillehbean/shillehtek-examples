// Initialize a single MAX7219 8x8 matrix and display the static text "HI" using the MD_Parola library.
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
#define MAX_DEVICES 1     // change to 4 if using the 4-in-1 module
#define CS_PIN 10

MD_Parola display = MD_Parola(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  display.begin();
  display.setIntensity(2);   // 0-15 brightness
  display.displayClear();
  display.print("HI");
}

void loop() {}
