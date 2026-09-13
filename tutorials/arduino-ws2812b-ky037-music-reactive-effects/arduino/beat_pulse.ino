// Beat pulse function that captures audio peaks from A0, maps peak amplitude to brightness, fills the strip with color, and applies a decay.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ws2812b-ky037-music-reactive-effects
// Parts used: https://shillehtek.com/products/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30
//             https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void beatPulse() {
  static int peakHold = 0;
  int level = analogRead(A0);
  if (level > peakHold) peakHold = level;
  uint8_t brightness = constrain(map(peakHold, 100, 600, 0, 255), 0, 255);
  fill_solid(leds, NUM_LEDS, CHSV(millis() / 30 % 255, 255, brightness));
  FastLED.show();
  peakHold = peakHold * 0.9;  // decay
}
