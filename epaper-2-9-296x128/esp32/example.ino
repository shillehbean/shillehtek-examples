// Runs a numeric counter on an ESP32 using GxEPD2 with fast partial updates for the number area and occasional full refreshes to keep the display clean.
//
// Buy this module: https://shillehtek.com/products/e-ink-display-2-9-inch-296x128-spi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/e-ink-display-2-9-inch-296x128-spi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 2.9" e-Paper - ESP32 partial-refresh counter (GxEPD2)
// CS->5, DC->17, RST->16, BUSY->4, DIN->23, CLK->18

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold18pt7b.h>

GxEPD2_BW<GxEPD2_290_T94_V2, GxEPD2_290_T94_V2::HEIGHT>
  display(GxEPD2_290_T94_V2(5, 17, 16, 4));

int counter = 0;

void setup() {
  display.init(115200);
  display.setRotation(1);
  display.setFont(&FreeMonoBold18pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();          // one full refresh at boot
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(20, 50);
    display.print("Counter:");
  } while (display.nextPage());
}

void loop() {
  // fast partial update of just the number area
  display.setPartialWindow(20, 70, 200, 40);
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(20, 100);
    display.print(counter);
  } while (display.nextPage());

  counter++;
  delay(3000);
  if (counter % 20 == 0) display.refresh();   // periodic full clean
}
