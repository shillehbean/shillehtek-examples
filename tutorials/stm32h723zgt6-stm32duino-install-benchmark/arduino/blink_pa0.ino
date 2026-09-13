// Blinks an LED connected to pin PA0 with a 500 ms on/off period.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32h723zgt6-stm32duino-install-benchmark
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-stm32h723zgt6-core-development-board
//             https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
//             https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LED = PA0;

void setup() {
  pinMode(LED, OUTPUT);
}

void loop() {
  digitalWrite(LED, HIGH);
  delay(500);
  digitalWrite(LED, LOW);
  delay(500);
}
