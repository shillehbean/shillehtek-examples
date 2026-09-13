// ESP32 Arduino sketch using the GxEPD2 library to initialize the 2.13" e-paper, render text with a font, update the display, and enter hibernate (low-power) mode.
//
// Buy this module: https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 2.13" Black & White E-Paper - ESP32 Arduino Example
// Library: GxEPD2 by Jean-Marc Zingg (install via Library Manager)

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

// CS=5, DC=17, RST=16, BUSY=4
GxEPD2_BW<GxEPD2_213_BN, GxEPD2_213_BN::HEIGHT>
  display(GxEPD2_213_BN(/*CS=*/5, /*DC=*/17, /*RST=*/16, /*BUSY=*/4));

void setup() {
  Serial.begin(115200);
  display.init(115200);
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);

  display.setFullWindow();
  display.firstPage();
  do {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(10, 30);
    display.print("Hello, ShillehTek!");
    display.setCursor(10, 60);
    display.print("2.13\" E-Paper");
  } while (display.nextPage());

  display.hibernate(); // low-power sleep
}

void loop() {}
