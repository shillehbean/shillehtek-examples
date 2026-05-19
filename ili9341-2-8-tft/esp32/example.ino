// Uses the TFT_eSPI library on an ESP32 to initialize the ILI9341, set rotation, draw text, and render simple shapes (rectangle and filled circle).
//
// Buy this module: https://shillehtek.com/products/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// Install "TFT_eSPI" library and configure User_Setup.h
// for ILI9341 + your ESP32 SPI pins.

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);

  tft.setTextFont(4);
  tft.setTextColor(TFT_GREEN, TFT_BLACK);
  tft.drawString("ESP32 + ILI9341", 20, 30);

  // Some shapes
  tft.drawRect(20, 80, 280, 60, TFT_WHITE);
  tft.fillCircle(160, 200, 40, TFT_RED);
}

void loop() {}
