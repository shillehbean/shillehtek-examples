// Complete Arduino sketch that initializes the ST7735 display, draws static text, and updates a yellow numeric counter every 500 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-st7735-tft-drive-color-display
// Parts used: https://shillehtek.com/products/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

#define TFT_CS  9
#define TFT_RST 7
#define TFT_DC  8

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(6, 8);
  tft.setTextColor(ST77XX_CYAN);
  tft.setTextSize(2);
  tft.print("ShillehTek");

  tft.setCursor(6, 36);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(1);
  tft.print("1.8\" ST7735 demo");
}

unsigned long counter = 0;

void loop() {
  tft.fillRect(6, 60, 120, 16, ST77XX_BLACK);
  tft.setCursor(6, 60);
  tft.setTextColor(ST77XX_YELLOW);
  tft.setTextSize(2);
  tft.print(counter++);
  delay(500);
}
