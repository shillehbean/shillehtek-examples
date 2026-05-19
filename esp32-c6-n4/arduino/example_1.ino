// Cycle the onboard WS2812 RGB LED on GPIO8 through red, green, and blue colors using the Adafruit NeoPixel library.
//
// Buy this module: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c6-n4-dev-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Blink the onboard WS2812 RGB LED on GPIO8.
// Requires the "Adafruit NeoPixel" library (install via Library Manager).

#include <Adafruit_NeoPixel.h>

#define LED_PIN   8
#define NUM_LEDS  1

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.setBrightness(30);
}

void loop() {
  strip.setPixelColor(0, strip.Color(255, 0, 0)); strip.show(); delay(500);
  strip.setPixelColor(0, strip.Color(0, 255, 0)); strip.show(); delay(500);
  strip.setPixelColor(0, strip.Color(0, 0, 255)); strip.show(); delay(500);
}
