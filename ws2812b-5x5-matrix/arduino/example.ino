// Arduino sketch using Adafruit_NeoPixel to map a 5x5 WS2812B matrix (optional serpentine indexing), run an index test to show pixel order, and draw a 5x5 heart in alternating colors.
//
// Buy this module: https://shillehtek.com/products/ws2812b-5x5-rgb-led-matrix-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812b-5x5-rgb-led-matrix-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// WS2812B 5x5 Matrix - Arduino Example
// DIN->D6 via 330 ohm, VCC->5V, GND->GND
// Library: "Adafruit NeoPixel"

#include <Adafruit_NeoPixel.h>

#define PIN   6
#define W     5
#define H     5
#define NUM   (W * H)
bool SERPENTINE = false;        // set true if the index test zigzags

Adafruit_NeoPixel px(NUM, PIN, NEO_GRB + NEO_KHZ800);

int xy(int x, int y) {          // (0,0) = first pixel at DIN
  if (SERPENTINE && (y % 2 == 1)) return y * W + (W - 1 - x);
  return y * W + x;
}

// 5x5 heart bitmap
const uint8_t HEART[5] = {0b01010, 0b11111, 0b11111, 0b01110, 0b00100};

void indexTest() {
  for (int i = 0; i < NUM; i++) {
    px.clear();
    px.setPixelColor(i, 0, 150, 255);
    px.show();
    delay(150);
  }
}

void drawHeart(uint32_t color) {
  px.clear();
  for (int y = 0; y < H; y++)
    for (int x = 0; x < W; x++)
      if (HEART[y] & (1 << (W - 1 - x)))
        px.setPixelColor(xy(x, y), color);
  px.show();
}

void setup() {
  px.begin();
  px.setBrightness(50);
  indexTest();                  // watch the order once at startup
}

void loop() {
  drawHeart(px.Color(255, 0, 40));  delay(500);
  drawHeart(px.Color(255, 80, 0));  delay(500);
  drawHeart(px.Color(150, 0, 255)); delay(500);
}
