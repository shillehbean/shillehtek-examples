// ESP32-C6 Zigbee coordinator sketch that forms a Zigbee network and exposes a switch endpoint which can send on/off commands to paired light endpoints when the button is used.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c6-zigbee-light-switch-network
// Parts used: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#ifndef ZIGBEE_MODE_ZCZR
#error "Zigbee coordinator mode is not selected in Tools->Zigbee mode"
#endif

#include "Zigbee.h"

#define SWITCH_ENDPOINT_NUMBER 5
#define GPIO_INPUT_IO_TOGGLE_SWITCH BOOT_PIN  // or an external button

ZigbeeSwitch zbSwitch = ZigbeeSwitch(SWITCH_ENDPOINT_NUMBER);

void setup() {
  Serial.begin(115200);
  Zigbee.addEndpoint(&zbSwitch);
  Zigbee.begin(ZIGBEE_COORDINATOR);   // form the network
  // button handling binds presses to on/off commands
  // sent to the paired light endpoint
}
