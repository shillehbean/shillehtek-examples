// Sets up the TFT_eSPI driver on ESP32, configures rotation, clears the screen, and prints two text lines with different colors and sizes.
//
// Buy this module: https://shillehtek.com/products/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering-manual
// More examples: https://github.com/shillehtek/examples
//

// 1.8" TFT LCD ST7735 - ESP32 with TFT_eSPI
// Configure your pins in TFT_eSPI/User_Setup.h:
//   #define ST7735_DRIVER
//   #define TFT_WIDTH  128
//   #define TFT_HEIGHT 160
//   #define ST7735_BLACKTAB
//   #define TFT_MOSI 23
//   #define TFT_SCLK 18
//   #define TFT_CS    5
//   #define TFT_DC    2
//   #define TFT_RST   4

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.setCursor(8, 8);
  tft.println("ShillehTek");

  tft.setTextColor(TFT_CYAN);
  tft.setTextSize(1);
  tft.setCursor(8, 36);
  tft.println("ESP32 + ST7735");
}

void loop() {}
