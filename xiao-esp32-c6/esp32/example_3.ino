// Initializes NimBLE and starts BLE advertising with the device name 'ShillehTek-C6'.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO ESP32-C6 - Simple BLE Advertise (5.3 LE)
// Uses NimBLE-Arduino: install from Library Manager.

#include <NimBLEDevice.h>

void setup() {
  Serial.begin(115200);
  NimBLEDevice::init("ShillehTek-C6");

  NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
  adv->setName("ShillehTek-C6");
  adv->start();
  Serial.println("Advertising...");
}

void loop() {
  delay(1000);
}
