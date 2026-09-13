// Initialize a TM1637 4-digit LED display, set brightness, and show the number 1234.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-tm1637-ssd1306-epaper-pick-display
// Parts used: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
//             https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
//             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <TM1637Display.h>
TM1637Display d(CLK, DIO);
d.setBrightness(7);
d.showNumberDec(1234);
