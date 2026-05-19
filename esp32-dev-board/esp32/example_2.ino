// Initializes the ESP32 as a BLE peripheral and starts advertising with the device name "ShillehTek-ESP32".
//
// Buy this module: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-dev-board-cp2102-type-c-4mb-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP-WROOM-32 - advertise as a BLE peripheral

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ShillehTek-ESP32");
  BLEServer* server = BLEDevice::createServer();
  BLEAdvertising* adv = BLEDevice::getAdvertising();
  adv->setScanResponse(true);
  adv->start();
  Serial.println("Advertising as ShillehTek-ESP32");
}

void loop() { delay(2000); }
