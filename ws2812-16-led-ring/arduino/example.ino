// Arduino example using the Adafruit_NeoPixel library to run spinner and gauge animations on the WS2812 16-LED ring connected to digital pin D6.
//
// Buy this module: https://shillehtek.com/products/ws2812-16-led-addressable-rgb-ring
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-16-led-addressable-rgb-ring-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// WS2812 16-LED Ring - Arduino Example
// DI->D6 via 330 ohm, 5V->5V, GND->GND
// Library: "Adafruit NeoPixel"

#include <Adafruit_NeoPixel.h>

#define PIN      6
#define NUM      16

Adafruit_NeoPixel ring(NUM, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(60);
  ring.show();
}

void spinner(uint32_t color, int loops) {
  for (int t = 0; t < loops * NUM; t++) {
    ring.clear();
    ring.setPixelColor(t % NUM, color);
    ring.setPixelColor((t + 1) % NUM, color);        // 2-px head
    ring.setPixelColor((t + NUM - 1) % NUM,
                       ring.Color(10, 10, 30));      // faint tail
    ring.show();
    delay(60);
  }
}

void gauge(int percent) {                            // 0-100
  int lit = map(percent, 0, 100, 0, NUM);
  ring.clear();
  for (int i = 0; i < lit; i++) {
    // green -> yellow -> red as the gauge fills
    uint8_t r = map(i, 0, NUM - 1, 0, 255);
    uint8_t g = map(i, 0, NUM - 1, 255, 0);
    ring.setPixelColor(i, r, g, 0);
  }
  ring.show();
}

void loop() {
  spinner(ring.Color(0, 120, 255), 4);

  for (int p = 0; p <= 100; p += 5) {                // gauge sweep
    gauge(p);
    delay(80);
  }
  delay(600);
}
