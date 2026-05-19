// Transmit a 433 MHz code from an Arduino using a TX module and the rc-switch library to emulate the relay's wireless remote button.
//
// Buy this module: https://shillehtek.com/products/433mhz-12v-1-channel-relay-module-with-wireless-remote
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/433mhz-12v-1-channel-relay-module-with-wireless-remote-manual
// More examples: https://github.com/shillehtek/examples
//

// Fake the wireless remote from an Arduino + cheap 433 MHz TX module
// Library: rc-switch by sui77

#include <RCSwitch.h>

RCSwitch tx = RCSwitch();

void setup() {
  tx.enableTransmit(10);    // TX module DATA pin
  tx.setProtocol(1);
  tx.setPulseLength(350);
}

void loop() {
  // Replace 1234567 with the code your remote actually sends.
  // To find it: run rc-switch's ReceiveDemo with a separate RX module
  // and press the remote's button.
  tx.send(1234567, 24);
  delay(2000);
}
