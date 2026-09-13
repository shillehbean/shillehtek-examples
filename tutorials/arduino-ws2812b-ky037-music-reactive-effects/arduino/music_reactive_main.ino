// Main Arduino sketch that initializes FastLED and runs a simple rainbow sweep across the WS2812B strip.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ws2812b-ky037-music-reactive-effects
// Parts used: https://shillehtek.com/products/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30
//             https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <FastLED.h>
#define NUM_LEDS 60
#define DATA_PIN 6
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // simple rainbow sweep
  static uint8_t hue = 0;
  fill_rainbow(leds, NUM_LEDS, hue++, 7);
  FastLED.show();
  delay(20);
}
