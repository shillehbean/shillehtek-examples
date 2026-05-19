// Blink a LED connected to PB0 (or the built-in LED if wired to PB0) with a 500 ms on/off period using the Arduino-style API on the STM32 board.
//
// Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-stm32h723zgt6-core-development-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-stm32h723zgt6-core-development-board-manual
// More examples: https://github.com/shillehtek/examples
//

// STM32H723ZGT6 - Blink built-in or external LED
// Board: "Generic STM32H7 Series", Variant: STM32H723ZGTx
// Upload Method: STM32CubeProgrammer (SWD)

#define LED_PIN PB0   // change to your wired LED pin

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
