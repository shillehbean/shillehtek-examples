// Use an Arduino with a 433 MHz RX module and rc-switch to receive and print the remote's numeric code and bit length for learning the remote signal.
//
// Buy this module: https://shillehtek.com/products/433mhz-12v-1-channel-relay-module-with-wireless-remote
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/433mhz-12v-1-channel-relay-module-with-wireless-remote-manual
// More examples: https://github.com/shillehtek/examples
//

// Use a 433 MHz RX module + Arduino to learn what code the remote sends
// Library: rc-switch by sui77

#include <RCSwitch.h>

RCSwitch rx = RCSwitch();

void setup() {
  Serial.begin(9600);
  rx.enableReceive(0);  // Interrupt 0 = D2 on UNO
}

void loop() {
  if (rx.available()) {
    Serial.print("Code: ");
    Serial.print(rx.getReceivedValue());
    Serial.print("  Bits: ");
    Serial.println(rx.getReceivedBitlength());
    rx.resetAvailable();
  }
}
