// Blinks digital pin D8 on the Arduino (5V side) at 1 Hz to verify the corresponding TXS0108E channel reflects the signal to the 3.3V side.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-txs0108e-3-3v-5v-level-shift
// Parts used: https://shillehtek.com/products/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Toggle pin D8 on the 5V side; B1 on the TXS0108E reflects to A1 on the 3.3V side.
void setup() { pinMode(8, OUTPUT); }
void loop() {
  digitalWrite(8, HIGH); delay(500);
  digitalWrite(8, LOW);  delay(500);
}
