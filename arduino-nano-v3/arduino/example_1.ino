// Blink the onboard LED on D13 (LED_BUILTIN) on and off with a 1 second period.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-presoldered-ch340g-atmega328p-manual
// More examples: https://github.com/shillehtek/examples
//

// Blink the onboard yellow LED wired to D13.
// The classic "Hello World" of microcontrollers.

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // LED_BUILTIN = D13 on the Nano
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}
