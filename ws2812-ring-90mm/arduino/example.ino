// Arduino sketch using the Adafruit_NeoPixel library to run comet and rainbow animations (and a partial clock-sweep) on the 24-LED WS2812 ring.
//
// Buy this module: https://shillehtek.com/products/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ws2812-led-ring-90mm-arduino-raspberry-pi-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// WS2812 24-LED Ring - Arduino Example
// DI->D6 via 330 ohm, 5V->5V, GND->GND
// Library: "Adafruit NeoPixel" (Library Manager)

#include <Adafruit_NeoPixel.h>

#define PIN        6
#define NUM_LEDS   24

Adafruit_NeoPixel ring(NUM_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  ring.begin();
  ring.setBrightness(60);            // 0-255; keep low on USB power
  ring.show();
}

void comet(uint32_t color, int loops) {
  for (int t = 0; t < loops * NUM_LEDS; t++) {
    ring.clear();
    for (int tail = 0; tail < 6; tail++) {
      int i = (t - tail + NUM_LEDS * 8) % NUM_LEDS;
      uint8_t fade = 255 >> tail;
      uint8_t r = (uint8_t)(color >> 16) * fade / 255;
      uint8_t g = (uint8_t)(color >> 8)  * fade / 255;
      uint8_t b = (uint8_t)(color)       * fade / 255;
      ring.setPixelColor(i, r, g, b);
    }
    ring.show();
    delay(40);
  }
}

void rainbow(int loops) {
  for (int j = 0; j < 256 * loops; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      ring.setPixelColor(i, ring.gamma32(
        ring.ColorHSV((i * 65536L / NUM_LEDS + j * 256) & 0xFFFF)));
    }
    ring.show();
    delay(10);
  }
}

void clockSweep(int loops) {
  for (int t = 0; t < loops * NUM_LEDS; t++) {
    ring.clear();
    ring.setPixelColor(t % NUM_LEDS, 255, 40, 0);      // hand
    ring.setPixelColor(0, 40, 40, 40);                 // 12 o'clock mark
    ring.show();
    delay(120);
  }
}

void loop() {
  comet(ring.Color(0, 120, 255), 3);
  rainbow(2);
  clockSweep(2);
}
