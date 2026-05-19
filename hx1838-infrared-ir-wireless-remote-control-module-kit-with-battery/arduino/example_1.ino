// Reads incoming IR signals with the IRremote library and prints the decoded command hex code to Serial.
//
// Buy this module: https://shillehtek.com/products/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery-manual
// More examples: https://github.com/shillehtek/examples
//

// HX1838 IR Remote - Arduino Example
// Library: IRremote by shirriff (v3+ syntax)

#include <IRremote.hpp>

const int IR_PIN = 2;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  Serial.println("Press a button...");
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Code: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();  // ready for next code
  }
}
