// Shows the three possible tft.initR(...) calls for different ST7735 PCB/tab variants so you can pick the correct initialization for your module.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-st7735-tft-drive-color-display
// Parts used: https://shillehtek.com/products/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering
// More examples: https://github.com/shillehbean/shillehtek-examples
//

tft.initR(INITR_BLACKTAB);   // most red-PCB 1.8" modules
// tft.initR(INITR_GREENTAB);   // try this if reds and blues swap
// tft.initR(INITR_REDTAB);     // last resort, older boards
