// Blink the Digispark onboard LED on pin P1 (change to P0 if your board revision uses P0).
//
// Buy this module: https://shillehtek.com/products/attiny85-digispark-usb-arduino-development-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/attiny85-digispark-usb-arduino-development-board-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Digispark ATtiny85 - Blink the onboard LED
// LED is on P1 (change to 0 if your revision uses P0)

const int LED_PIN = 1;

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(300);
  digitalWrite(LED_PIN, LOW);
  delay(300);
}
