// Perform a BLE scan using the NimBLE stack and list discovered devices' addresses and RSSI values.
//
// Buy this module: https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c6-n4-dev-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Scan for nearby BLE devices and print their addresses and RSSI.
// Uses the built-in NimBLE-Arduino stack included with esp32 board v3.x.

#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;
const int scanTime = 5;  // seconds

void setup() {
  Serial.begin(115200);
  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  Serial.println("Scanning BLE...");
  BLEScanResults results = pBLEScan->start(scanTime, false);
  Serial.printf("Found %d devices\n", results.getCount());
  for (int i = 0; i < results.getCount(); i++) {
    BLEAdvertisedDevice d = results.getDevice(i);
    Serial.printf("  %s  RSSI: %d\n", d.getAddress().toString().c_str(), d.getRSSI());
  }
  pBLEScan->clearResults();
  delay(2000);
}
