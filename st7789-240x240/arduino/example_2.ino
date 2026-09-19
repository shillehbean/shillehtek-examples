// Configures the ST7789 at a 40 MHz SPI clock and runs a simple color-wipe animation by filling 8-pixel horizontal stripes with several colors.
//
// Buy this module: https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tft-lcd-1-3-240x240-st7789-esp32-arduino-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

Adafruit_ST7789 tft = Adafruit_ST7789(-1, 16, 17);  // CS=-1, DC, RST

void setup() {
  tft.init(240, 240, SPI_MODE3);
  tft.setSPISpeed(40000000);       // 40 MHz
  tft.fillScreen(ST77XX_BLACK);
}

void loop() {
  // color wipe animation
  uint16_t colors[] = {ST77XX_RED, ST77XX_GREEN, ST77XX_BLUE,
                       ST77XX_YELLOW, ST77XX_CYAN, ST77XX_MAGENTA};
  for (int i = 0; i < 6; i++) {
    for (int y = 0; y < 240; y += 8) {
      tft.fillRect(0, y, 240, 8, colors[i]);
    }
  }
}
