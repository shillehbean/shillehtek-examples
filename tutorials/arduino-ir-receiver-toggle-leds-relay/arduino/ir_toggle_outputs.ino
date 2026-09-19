// Sketch that listens for two specific IR button codes and toggles two digital outputs (pins 8 and 9), ignoring NEC repeat frames so one press equals one toggle.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ir-receiver-toggle-leds-relay
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/1-channel-5v-relay-module
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <IRremote.hpp>

#define BTN_1 0x45      // replace with YOUR codes from Step 2
#define BTN_2 0x46

bool led1 = false, led2 = false;

void setup() {
  IrReceiver.begin(3, ENABLE_LED_FEEDBACK);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    // ignore NEC auto-repeat frames so one press = one toggle
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {
      switch (IrReceiver.decodedIRData.command) {
        case BTN_1: led1 = !led1; digitalWrite(8, led1); break;
        case BTN_2: led2 = !led2; digitalWrite(9, led2); break;
      }
    }
    IrReceiver.resume();
  }
}
