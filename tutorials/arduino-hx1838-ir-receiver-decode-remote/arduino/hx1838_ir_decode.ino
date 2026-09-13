// Initialize the IR receiver on pin 2, decode incoming remote signals, and print the command byte as a hexadecimal code to Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hx1838-ir-receiver-decode-remote
// Parts used: https://shillehtek.com/products/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <IRremote.h>
const int IR_PIN = 2;
void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
}
void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Code: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();
  }
}
