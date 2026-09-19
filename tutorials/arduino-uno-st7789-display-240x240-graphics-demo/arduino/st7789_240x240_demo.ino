// Arduino sketch that initializes a 240x240 ST7789 SPI display using Adafruit_GFX and Adafruit_ST7789, clears the screen, sets rotation, and prints a "Hello, world!" message.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-st7789-display-240x240-graphics-demo
// Parts used: https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>             // Arduino SPI library

#define TFT_CS   10  // this 7-pin module has no CS pin; define is unused
#define TFT_RST   8  // reset pin
#define TFT_DC    9  // data/command pin

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

float p = 3.1415926;  // used by the graphics/math demos

void setup() {
  Serial.begin(9600);
  Serial.println(F("Hello! ST7789 TFT Test"));

  tft.init(240, 240, SPI_MODE2);  // 240x240, MODE2 for no-CS modules
  tft.setRotation(2);             // remove this line if your image is flipped
  Serial.println(F("Initialized"));

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(30, 110);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.print("Hello, world!");
  delay(1000);
  // ...print test, shapes, and animation demos follow
}

void loop() {
}
