// Blink the onboard LED on D13 (LED_BUILTIN) at a 1 Hz rate.
//
// Buy this module: https://shillehtek.com/products/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-nano-v3-0-atmega328p-16mhz-ch340c-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Blink the onboard LED (connected to D13)
// The classic "Hello World" of microcontrollers

void setup() {
  // Configure pin D13 (LED_BUILTIN) as an output
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // Turn LED on
  delay(1000);                       // Wait 1 second
  digitalWrite(LED_BUILTIN, LOW);    // Turn LED off
  delay(1000);                       // Wait 1 second
}
