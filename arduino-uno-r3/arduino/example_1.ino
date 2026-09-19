// Blinks the board's built-in LED on pin 13 at a 1 Hz rate (500 ms on, 500 ms off).
//
// Buy this module: https://shillehtek.com/products/arduino-uno-r3-starter-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-uno-r3-starter-kit-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// The "hello world" of hardware - uses the LED built into the board
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);   // pin 13 on the Uno
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}
