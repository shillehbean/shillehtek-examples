// VU meter function that reads the KY-037 analog output (A0) and lights LEDs up to the measured peak using a rainbow ramp.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ws2812b-ky037-music-reactive-effects
// Parts used: https://shillehtek.com/products/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30
//             https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void vuMeter() {
  int level = analogRead(A0);
  int peak = constrain(map(level, 0, 600, 0, NUM_LEDS), 0, NUM_LEDS);
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i < peak) {
      leds[i] = CHSV(i * 4, 255, 255);   // rainbow ramp
    } else {
      leds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}
