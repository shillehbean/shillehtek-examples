// Creates a breathing single-color (blue) effect across all 64 LEDs using Adafruit_NeoPixel on Arduino.
//
// Buy this module: https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_NeoPixel.h>

#define PIN 16
Adafruit_NeoPixel px(64, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  px.begin();
  px.setBrightness(40);
}

void loop() {
  // breathing single color
  for (int b = 0; b <= 255; b += 5) { fillAll(0, b / 2, b); delay(15); }
  for (int b = 255; b >= 0; b -= 5) { fillAll(0, b / 2, b); delay(15); }
}

void fillAll(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < 64; i++) px.setPixelColor(i, r, g, b);
  px.show();
}
