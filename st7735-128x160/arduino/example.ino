// Initializes an Adafruit ST7735 display on Arduino, clears the screen, writes two text lines and draws a red rectangle.
//
// Buy this module: https://shillehtek.com/products/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering-manual
// More examples: https://github.com/shillehtek/examples
//

// 1.8" TFT LCD ST7735 - Arduino Example
// Libraries: Adafruit_GFX, Adafruit_ST7735, SPI

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS    10
#define TFT_RST    9
#define TFT_DC     8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Use INITR_BLACKTAB for the red 1.8" 128x160 board
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.fillScreen(ST77XX_BLACK);

  tft.setCursor(8, 8);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.println("ShillehTek");

  tft.setCursor(8, 36);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(1);
  tft.println("1.8\" TFT 128x160");

  tft.drawRect(4, 4, 152, 120, ST77XX_RED);
}

void loop() {}
