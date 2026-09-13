// Initializes the ILI9341 SPI TFT, sets up a landscape screen, draws title text and two rounded buttons labeled Start and About.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ili9341-touchscreen-build-touch-ui
// Parts used: https://shillehtek.com/products/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

const int TFT_CS  = 10;
const int TFT_DC  = 8;
const int TFT_RST = 9;
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

void drawButton(int x, int y, int w, int h, const char* label) {
  tft.fillRoundRect(x, y, w, h, 6, ILI9341_BLUE);
  tft.drawRoundRect(x, y, w, h, 6, ILI9341_WHITE);
  tft.setCursor(x + 14, y + 14);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(2);
  tft.print(label);
}

void setup() {
  Serial.begin(9600);
  tft.begin();
  tft.setRotation(1);   // landscape
  tft.fillScreen(ILI9341_BLACK);

  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.setCursor(20, 20);
  tft.println("ShillehTek");
  tft.setTextSize(2);
  tft.setCursor(20, 60);
  tft.setTextColor(ILI9341_WHITE);
  tft.println("ILI9341 demo");

  drawButton(20,  140, 130, 50, "Start");
  drawButton(170, 140, 130, 50, "About");
}

void loop() {}
