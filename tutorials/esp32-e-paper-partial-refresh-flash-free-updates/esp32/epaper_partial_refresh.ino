// Initializes a Waveshare 2.9-inch e-paper display and demonstrates using GxEPD2 and U8g2 to draw a full-refresh static layout and perform flash-free partial refreshes to update an uptime value every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-e-paper-partial-refresh-flash-free-updates
// Parts used: https://shillehtek.com/products/e-ink-display-2-9-inch-296x128-spi
//             https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <U8g2_for_Adafruit_GFX.h>

// Waveshare 2.9" V2 panel (GDEM029T94) - change the class for other panels
GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT>
  display(GxEPD2_290_T94_V2(/*CS*/ 5, /*DC*/ 17, /*RST*/ 16, /*BUSY*/ 4));

U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

void setup() {
  display.init();
  display.setRotation(1);
  u8g2Fonts.begin(display);
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);

  // full refresh: draw the static layout once
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    u8g2Fonts.setFont(u8g2_font_helvB14_tf);
    u8g2Fonts.setCursor(10, 30);
    u8g2Fonts.print("Uptime (ms):");
  } while (display.nextPage());
}

void loop() {
  // partial update: redraw ONLY the value box (~0.3 s, no flash)
  display.setPartialWindow(10, 50, 200, 40);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    u8g2Fonts.setFont(u8g2_font_logisoso28_tf);
    u8g2Fonts.setCursor(10, 85);
    u8g2Fonts.print(int(millis()));
  } while (display.nextPage());

  delay(1000);
}
