// Reads incoming IR remote codes with the IRremote library and prints the received values in hexadecimal to the Serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hx1838-vs1838-ir-receiver-choose
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-5v-relay-module
//             https://shillehtek.com/products/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <IRremote.h>
const int IR_PIN = 2;
IRrecv ir(IR_PIN);
decode_results res;

void setup() {
  Serial.begin(9600);
  ir.enableIRIn();
}

void loop() {
  if (ir.decode(&res)) {
    Serial.println(res.value, HEX);
    ir.resume();
  }
}
