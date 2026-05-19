// Toggles the Pro Micro's built-in TX and RX LEDs (active-LOW) every 500 ms to provide a blink indicator since there's no dedicated user LED pin.
//
// Buy this module: https://shillehtek.com/products/manual
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pro-micro-atmega32u4-5v-16mhz-presoldered-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Blink the onboard TX/RX LEDs since the Pro Micro has no
// dedicated user LED on a GPIO pin. D13 is not an LED here.

void setup() {
  // Both built-in LEDs are available:
  // LED_BUILTIN_TX (PD5) and LED_BUILTIN_RX (PB0)
  pinMode(LED_BUILTIN_TX, OUTPUT);
  pinMode(LED_BUILTIN_RX, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN_TX, LOW);   // LEDs are active-LOW
  digitalWrite(LED_BUILTIN_RX, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN_TX, HIGH);
  digitalWrite(LED_BUILTIN_RX, LOW);
  delay(500);
}
