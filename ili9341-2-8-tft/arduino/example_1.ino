// Initializes the ILI9341 using the Adafruit_ILI9341 and Adafruit_GFX libraries, sets rotation, clears the screen, and prints multi-colored text ('Hello, ILI9341!').
//
// Buy this module: https://shillehtek.com/products/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// Install: Adafruit ILI9341 + Adafruit GFX Library

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST   8

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(ILI9341_BLACK);

  tft.setCursor(20, 20);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.println("Hello,");
  tft.setTextColor(ILI9341_CYAN);
  tft.println("ILI9341!");
}

void loop() {}
