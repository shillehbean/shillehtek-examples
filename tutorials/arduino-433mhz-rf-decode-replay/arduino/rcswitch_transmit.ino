// Sends predefined 433 MHz RF codes using the RCSwitch transmitter to toggle remote sockets (on/off) with a 2-second interval.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-433mhz-rf-decode-replay
// Parts used: https://shillehtek.com/products/433mhz-rf-transmitter-receiver-module-pair
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <RCSwitch.h>
RCSwitch sw = RCSwitch();

void setup() {
  sw.enableTransmit(10);   // D10
}

void loop() {
  sw.send(5592371, 24);    // socket 1 ON  - replace with your code/bits
  delay(2000);
  sw.send(5592380, 24);    // socket 1 OFF
  delay(2000);
}
