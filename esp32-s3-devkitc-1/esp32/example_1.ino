// Drives the onboard WS2812 RGB LED on GPIO38 using the Adafruit NeoPixel library and cycles red, green, and blue colors every 500 ms.
//
// Buy this module: https://shillehtek.com/products/esp32-s3-devkitc-1-presoldered-headers
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-devkitc-1-presoldered-headers-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32-S3 DevKitC-1 onboard RGB LED (WS2812 on GPIO38).
// Install "Adafruit NeoPixel" from Library Manager.

#include <Adafruit_NeoPixel.h>

#define LED_PIN   38
#define NUM_LEDS  1

Adafruit_NeoPixel led(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  led.begin();
  led.setBrightness(40);
  led.show();
}

void loop() {
  led.setPixelColor(0, led.Color(255, 0, 0)); led.show(); delay(500);
  led.setPixelColor(0, led.Color(0, 255, 0)); led.show(); delay(500);
  led.setPixelColor(0, led.Color(0, 0, 255)); led.show(); delay(500);
}
