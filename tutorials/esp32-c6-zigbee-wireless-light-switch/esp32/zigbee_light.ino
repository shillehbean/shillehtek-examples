// Zigbee end-device firmware implementing a light endpoint that controls an LED, handles button presses for local toggle and factory reset, and registers the endpoint with the Zigbee core.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c6-zigbee-wireless-light-switch
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
uint8_t led = 4;
uint8_t button = BOOT_PIN;
ZigbeeLight zbLight = ZigbeeLight(ZIGBEE_LIGHT_ENDPOINT);

void setLED(bool value) {
  digitalWrite(led, value);
}

void setup() {
  Serial.begin(115200);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  pinMode(button, INPUT_PULLUP);

  zbLight.setManufacturerAndModel("Espressif", "ZBLightBulb");
  zbLight.onLightChange(setLED);   // callback drives the LED

  Serial.println("Adding ZigbeeLight endpoint to Zigbee Core");
  Zigbee.addEndpoint(&zbLight);

  if (!Zigbee.begin()) {           // starts as an end device
    Serial.println("Zigbee failed to start! Rebooting...");
    ESP.restart();
  }
  Serial.println("Connecting to network");
  while (!Zigbee.connected()) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
}

void loop() {
  // Hold BOOT 3s = Zigbee factory reset; quick press = local toggle
  if (digitalRead(button) == LOW) {
    delay(100);
    int startTime = millis();
    while (digitalRead(button) == LOW) {
      delay(50);
      if ((millis() - startTime) > 3000) {
        Serial.println("Resetting Zigbee to factory and rebooting in 1s.");
        delay(1000);
        Zigbee.factoryReset();
      }
    }
    zbLight.setLight(!zbLight.getLightState());
  }
  delay(100);
}
