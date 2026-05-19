// Watches decoded IR button codes and switches an LED on or off based on specific hex values.
//
// Buy this module: https://shillehtek.com/products/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery-manual
// More examples: https://github.com/shillehtek/examples
//

// React to specific buttons. Run the previous sketch first
// to learn each button's hex code, then fill in below.

#include <IRremote.hpp>

const int IR_PIN = 2;
const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  IrReceiver.begin(IR_PIN);
}

void loop() {
  if (IrReceiver.decode()) {
    switch (IrReceiver.decodedIRData.command) {
      case 0x46: digitalWrite(LED_PIN, HIGH); break;  // UP
      case 0x15: digitalWrite(LED_PIN, LOW); break;   // DOWN
      case 0x40: /* OK button */ break;
    }
    IrReceiver.resume();
  }
}
