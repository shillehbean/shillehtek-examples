// Listens for a specific IR remote code and toggles a 5V relay output when the POWER code is received.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hx1838-vs1838-ir-receiver-choose
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int RELAY = 7;
const uint32_t POWER = 0xFFA25D;  // example
const uint32_t MUTE  = 0xFFE21D;
void setup() {
  pinMode(RELAY, OUTPUT); digitalWrite(RELAY, HIGH);
  ir.enableIRIn();
}
void loop() {
  if (ir.decode(&res)) {
    if (res.value == POWER) digitalWrite(RELAY, !digitalRead(RELAY));
    ir.resume();
  }
}
