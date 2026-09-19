// Initializes the GC9A01 with Adafruit_GFX, clears the screen, draws concentric circles and prints centered text.
//
// Buy this module: https://shillehtek.com/products/round-1-28in-ips-lcd-gc9a01-240x240-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/round-1-28in-ips-lcd-gc9a01-240x240-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: "Adafruit GC9A01A" + "Adafruit GFX"
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

#define TFT_CS  10
#define TFT_DC   7
#define TFT_RST  8

Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);

  // dial face: rings + centered text
  tft.drawCircle(120, 120, 118, GC9A01A_CYAN);
  tft.drawCircle(120, 120, 110, GC9A01A_DARKGREY);
  tft.setTextColor(GC9A01A_WHITE);
  tft.setTextSize(3);
  tft.setCursor(58, 105);
  tft.print("ROUND!");
}

void loop() {}
