// Uses the GxEPD2 Arduino library to draw text, a rectangle and a fake gauge on the 2.9" e-Paper, performs a full refresh, then puts the display into hibernation to save power.
//
// Buy this module: https://shillehtek.com/products/e-ink-display-2-9-inch-296x128-spi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/e-ink-display-2-9-inch-296x128-spi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 2.9" e-Paper 296x128 - Arduino Example (GxEPD2)
// CS->10, DC->9, RST->8, BUSY->7, DIN->11, CLK->13
// Libraries: GxEPD2 + Adafruit GFX

#include <GxEPD2_BW.h>
#include <Fonts/FreeSansBold12pt7b.h>

// V2 2.9" panel; if your screen stays blank try GxEPD2_290 instead
GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT>
  display(GxEPD2_290_T94_V2(10, 9, 8, 7));   // CS, DC, RST, BUSY

void setup() {
  display.init(115200);
  display.setRotation(1);                    // landscape 296x128
  display.setFont(&FreeSansBold12pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 40);
    display.print("ShillehTek");
    display.setCursor(10, 75);
    display.print("2.9\" e-Paper");
    display.drawRect(10, 95, 276, 20, GxEPD_BLACK);
    display.fillRect(10, 95, 180, 20, GxEPD_BLACK);   // fake gauge
  } while (display.nextPage());

  display.hibernate();                       // ~0 power, image stays
}

void loop() {}
