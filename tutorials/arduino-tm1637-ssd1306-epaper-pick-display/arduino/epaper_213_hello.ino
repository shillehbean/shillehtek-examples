// Initialize a 2.13" GxEPD2 black-and-white e-paper display, clear the screen, draw "Hello!", and perform a full-page update.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-tm1637-ssd1306-epaper-pick-display
// Parts used: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
//             https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
//             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <GxEPD2_BW.h>
GxEPD2_BW<GxEPD2_213_BN, 122> epd(GxEPD2_213_BN(/*CS=*/8, /*DC=*/9, /*RST=*/12, /*BUSY=*/13));
epd.init();
epd.setFullWindow();
epd.firstPage();
do {
  epd.fillScreen(GxEPD_WHITE);
  epd.setCursor(10, 30);
  epd.print("Hello!");
} while (epd.nextPage());
