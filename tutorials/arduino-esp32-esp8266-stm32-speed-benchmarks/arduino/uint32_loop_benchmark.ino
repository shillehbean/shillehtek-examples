// Runs one million 32-bit multiply-add iterations, measures the elapsed time with micros(), and prints the result to Serial for a raw integer speed benchmark.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-esp32-esp8266-stm32-speed-benchmarks
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

void setup(){ Serial.begin(115200); }
void loop(){
  uint32_t a = 1;
  uint32_t t0 = micros();
  for(uint32_t i=0; i<1000000UL; i++){ a = a * 3 + 7; }
  Serial.println(micros() - t0);
  delay(1000);
}
