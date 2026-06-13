// Initializes the TFT_eSPI display, turns the backlight on, sets rotation and text style, and prints a single line of text to the screen.
//
// Buy this module: https://shillehtek.com/products/Display
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-lvgl-2-8-inch-240x320-smart-display-with-resistive-touch-wifi-bluetooth-dev-board-manual
// More examples: https://github.com/shillehtek/examples
//

#include <TFT_eSPI.h>

TFT_eSPI tft = TFT_eSPI();

void setup() {
  pinMode(21, OUTPUT);
  digitalWrite(21, HIGH);   // backlight ON
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_YELLOW, TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(20, 100);
  tft.println("CYD is alive!");
}

void loop() {}
