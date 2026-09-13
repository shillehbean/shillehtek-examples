// Chase effect function that advances a colored head along the strip while fading the tail for a moving-trail animation.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ws2812b-ky037-music-reactive-effects
// Parts used: https://shillehtek.com/products/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30
//             https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void chase() {
  static int head = 0;
  fadeToBlackBy(leds, NUM_LEDS, 30);
  leds[head] = CHSV(head * 4, 255, 255);
  head = (head + 1) % NUM_LEDS;
  FastLED.show();
  delay(20);
}
