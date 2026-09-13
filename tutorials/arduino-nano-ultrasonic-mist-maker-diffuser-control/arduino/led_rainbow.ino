// Controls a single WS2812B LED with a cycling hue and sets the relay control pin at startup.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ultrasonic-mist-maker-diffuser-control
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/non-waterproof-ws2812b-smd-led-strip-60-led-meter-flexible-5m-roll-5v-ip30
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <FastLED.h>
#define PIXEL 6
CRGB led[1];

void setup() {
  pinMode(7, OUTPUT);
  FastLED.addLeds<WS2812B, PIXEL, GRB>(led, 1);
  digitalWrite(7, HIGH);   // mist ON
}
void loop() {
  static uint8_t hue = 0;
  led[0] = CHSV(hue++, 255, 200);
  FastLED.show();
  delay(60);
}
