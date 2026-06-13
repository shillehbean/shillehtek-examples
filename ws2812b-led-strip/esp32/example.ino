// Runs FastLED on an ESP32 to drive 60 WS2812B LEDs (via RMT) and show a moving pixel with a fading trail (Sinelon effect).
//
// Buy this module: https://shillehtek.com/products/Addressable LED
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30-manual
// More examples: https://github.com/shillehtek/examples
//

// WS2812B Strip - ESP32 with FastLED (RMT-driven)
// DIN on GPIO 5, 60 LEDs

#include <FastLED.h>

#define DATA_PIN  5
#define NUM_LEDS  60
#define BRIGHTNESS 64

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  // Sinelon: a single moving pixel with fading trail
  fadeToBlackBy(leds, NUM_LEDS, 20);
  int pos = beatsin16(13, 0, NUM_LEDS - 1);
  leds[pos] += CHSV(millis() / 10, 200, 255);
  FastLED.show();
  delay(15);
}
