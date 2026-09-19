// ESP32-C6 Zigbee end-device sketch that implements a light endpoint which controls a local LED via received Zigbee commands and uses a button for factory reset.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c6-zigbee-light-switch-network
// Parts used: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#ifndef ZIGBEE_MODE_ED
#error "Zigbee end device mode is not selected in Tools->Zigbee mode"
#endif

#include "Zigbee.h"

#define ZIGBEE_LIGHT_ENDPOINT 10
uint8_t led = 4;                 // LED on GPIO4
uint8_t button = BOOT_PIN;       // hold to factory-reset the node

ZigbeeLight zbLight = ZigbeeLight(ZIGBEE_LIGHT_ENDPOINT);

void setLED(bool value) {
  digitalWrite(led, value);
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  zbLight.onLightChange(setLED);   // Zigbee commands drive the LED
  Zigbee.addEndpoint(&zbLight);
  Zigbee.begin();                  // join the network
}
