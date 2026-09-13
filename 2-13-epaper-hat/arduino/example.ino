// Arduino (AVR/Uno-compatible) sketch using GxEPD2_BW in paged drawing mode to print text to the 2.13" e-paper while conserving RAM, then hibernate the display.
//
// Buy this module: https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 2.13" Black & White E-Paper - Arduino Example
// Library: GxEPD2 by Jean-Marc Zingg
// CS=10, DC=9, RST=8, BUSY=7

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT>
  display(GxEPD2_213_BN(/*CS=*/10, /*DC=*/9, /*RST=*/8, /*BUSY=*/7));

void setup() {
  display.init();
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  // Paged drawing keeps RAM usage low on UNO (2 KB SRAM)
  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 30);
    display.print("Hello, ShillehTek!");
    display.setCursor(10, 60);
    display.print("2.13\" E-Paper");
  } while (display.nextPage());

  display.hibernate();
}

void loop() {}
