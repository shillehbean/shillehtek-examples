// Runs a 1,000,000-iteration floating-point multiply/add loop, measures the elapsed microseconds, and prints the timing to Serial every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32h723zgt6-stm32duino-install-benchmark
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-stm32h723zgt6-core-development-board
//             https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
//             https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup() {
  Serial.begin(115200);
}

void loop() {
  uint32_t t = micros();
  float a = 1.0f;

  for (uint32_t i = 0; i < 1000000UL; i++) {
    a = a * 1.0001f + 0.00001f;
  }

  Serial.printf("loop = %lu us\n", micros() - t);
  delay(1000);
}
