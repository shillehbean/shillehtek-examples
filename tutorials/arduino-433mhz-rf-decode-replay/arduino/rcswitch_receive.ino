// Listens for incoming 433 MHz RF codes with the RCSwitch receiver and prints the decoded value, bit length, protocol, and pulse delay to the serial monitor.
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
  Serial.begin(9600);
  sw.enableReceive(0);   // interrupt 0 = D2
}

void loop() {
  if (sw.available()) {
    Serial.print("code=");
    Serial.print(sw.getReceivedValue());
    Serial.print(" bits=");
    Serial.print(sw.getReceivedBitlength());
    Serial.print(" proto=");
    Serial.print(sw.getReceivedProtocol());
    Serial.print(" pulse=");
    Serial.println(sw.getReceivedDelay());
    sw.resetAvailable();
  }
}
