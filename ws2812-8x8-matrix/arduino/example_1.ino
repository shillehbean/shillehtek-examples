// Plays a moving diagonal rainbow across the 8x8 WS2812 matrix (supports serpentine wiring) using the Adafruit_NeoPixel Arduino library.
//
// Buy this module: https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Library Manager: install "Adafruit NeoPixel"
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define W 8
#define H 8
Adafruit_NeoPixel px(W * H, PIN, NEO_GRB + NEO_KHZ800);

// Set SERPENTINE true if every other row runs backwards on your panel
const bool SERPENTINE = false;

int xy(int x, int y) {
  if (SERPENTINE && (y % 2 == 1)) return y * W + (W - 1 - x);
  return y * W + x;
}

void setup() {
  px.begin();
  px.setBrightness(30);   // ~12% - keep low on USB power
}

void loop() {
  // moving diagonal rainbow
  for (int t = 0; t < 256; t += 4) {
    for (int y = 0; y < H; y++)
      for (int x = 0; x < W; x++)
        px.setPixelColor(xy(x, y),
          px.ColorHSV((t + (x + y) * 16) * 256));
    px.show();
    delay(30);
  }
}
