// Uses the FastLED library on an Arduino to drive a 30-LED WS2812B strip and display a continuous rainbow chase animation.
//
// Buy this module: https://shillehtek.com/products/Addressable LED
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// WS2812B Strip - Arduino with FastLED
// Install: FastLED library via Arduino Library Manager
// DIN on Digital Pin 6, 30 LEDs (cut from a longer strip)

#include <FastLED.h>

#define DATA_PIN  6
#define NUM_LEDS  30
#define BRIGHTNESS 64    // 0 - 255 (lower = less current draw)

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Rainbow chase
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 8), 255, 255);
  }
  FastLED.show();
  hue++;
  delay(20);
}
