// Initializes the ST7789 display (CS tied low) using SPI mode 3, sets rotation, clears the screen, and prints 'Hello IPS!' to the panel.
//
// Buy this module: https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tft-lcd-1-3-240x240-st7789-esp32-arduino-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: "Adafruit ST7735 and ST7789" + "Adafruit GFX"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS   -1   // this module has no CS pin
#define TFT_DC    9
#define TFT_RST   8

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.init(240, 240, SPI_MODE3);   // mode 3 because CS is tied low
  tft.setRotation(2);
  tft.fillScreen(ST77XX_BLACK);

  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.setCursor(20, 100);
  tft.print("Hello IPS!");
}

void loop() {}
