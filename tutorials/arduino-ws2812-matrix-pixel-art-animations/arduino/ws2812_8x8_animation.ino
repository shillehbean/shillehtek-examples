// Reads an 8x8 pixel frame stored in PROGMEM and displays it on a WS2812 (NeoPixel) matrix using FastLED; demonstrates how to add additional frames and cycle them for animations.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ws2812-matrix-pixel-art-animations
// Parts used: https://shillehtek.com/products/ws2812-8x8-led-matrix-arduino-esp32-raspberry-pi
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-universal-power-supply-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <avr/pgmspace.h>   // store frames in flash with PROGMEM
#include "FastLED.h"

#define NUM_LEDS 64
#define DATA_PIN 9

CRGB leds[NUM_LEDS];

// One 8x8 frame from LCD Image Converter (64 x 24-bit colors)
const long frame1[] PROGMEM = {
  0x000000, 0xff0000, 0x000000, /* ... 64 values total ... */
};

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(40);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = pgm_read_dword(&(frame1[i]));
  }
  FastLED.show();
  delay(500);
  // add frame2, frame3... and cycle them for animation
}
