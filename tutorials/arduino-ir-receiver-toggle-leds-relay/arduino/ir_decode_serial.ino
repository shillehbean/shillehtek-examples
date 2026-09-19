// Initial sketch that initializes an IR receiver on pin D3 and prints decoded remote button command values to the serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ir-receiver-toggle-leds-relay
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <IRremote.hpp>   // IRremote v3/v4 API

void setup() {
  Serial.begin(115200);
  IrReceiver.begin(3, ENABLE_LED_FEEDBACK);   // receiver on D3
}

void loop() {
  if (IrReceiver.decode()) {
    Serial.print("Button command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    IrReceiver.resume();                       // ready for next press
  }
}
