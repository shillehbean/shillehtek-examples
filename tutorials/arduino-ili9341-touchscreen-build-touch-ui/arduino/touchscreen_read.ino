// Reads touch input from a resistive touchscreen using the TouchScreen library and checks a pressure threshold to detect taps and report touch coordinates.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ili9341-touchscreen-build-touch-ui
// Parts used: https://shillehtek.com/products/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TouchScreen.h>

const int YP = A2, XM = A3, YM = 8, XP = 9;
TouchScreen ts(XP, YP, XM, YM, 300);

TSPoint p = ts.getPoint();
if (p.z > 50) {
  // tap detected at (p.x, p.y) - map to your buttons
}
