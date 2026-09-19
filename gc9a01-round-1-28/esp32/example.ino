// Animated gauge example that erases the old needle and draws a rotating needle from the display center in a loop.
//
// Buy this module: https://shillehtek.com/products/round-1-28in-ips-lcd-gc9a01-240x240-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/round-1-28in-ips-lcd-gc9a01-240x240-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

Adafruit_GC9A01A tft(5, 16, 17);   // CS, DC, RST

void setup() {
  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  tft.drawCircle(120, 120, 118, GC9A01A_WHITE);
}

void loop() {
  static float a = 0;
  // erase old needle, draw new one from center
  int x0 = 120 + cos(a) * 100, y0 = 120 + sin(a) * 100;
  tft.drawLine(120, 120, x0, y0, GC9A01A_BLACK);
  a += 0.05;
  int x1 = 120 + cos(a) * 100, y1 = 120 + sin(a) * 100;
  tft.drawLine(120, 120, x1, y1, GC9A01A_RED);
  delay(20);
}
