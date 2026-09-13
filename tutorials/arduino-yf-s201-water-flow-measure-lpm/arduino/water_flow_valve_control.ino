// Valve control sketch that uses a relay-controlled valve (active LOW) to stop flow when the accumulated total liters reaches a configured target.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-yf-s201-water-flow-measure-lpm
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const float TARGET_LITERS = 5.0;
const int VALVE = 7;

void setup() {
  pinMode(VALVE, OUTPUT);
  digitalWrite(VALVE, HIGH);   // valve OPEN (active LOW)
  // ...usual sensor setup...
}
void loop() {
  // ...update total_liters...
  if (total_liters >= TARGET_LITERS) {
    digitalWrite(VALVE, LOW);   // valve CLOSED
  }
}
