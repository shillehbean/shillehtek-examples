// Create a BLE GATT server that advertises a service with a notify characteristic and periodically sends a counter string as notifications.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-c3-devkit-arduino-wifi-ble-setup
// Parts used: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
//             https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SVC_UUID  "12345678-1234-1234-1234-1234567890ab"
#define CHAR_UUID "12345678-1234-1234-1234-1234567890ac"

BLECharacteristic* pChar;

void setup() {
  Serial.begin(115200);
  BLEDevice::init("ESP32-C3 Sensor");
  BLEServer*  pServer  = BLEDevice::createServer();
  BLEService* pService = pServer->createService(SVC_UUID);
  pChar = pService->createCharacteristic(
      CHAR_UUID,
      BLECharacteristic::PROPERTY_NOTIFY);
  pChar->addDescriptor(new BLE2902());
  pService->start();
  pServer->getAdvertising()->start();
  Serial.println("Advertising");
}

void loop() {
  static int count = 0;
  String s = "count=" + String(count++);
  pChar->setValue(s.c_str());
  pChar->notify();
  delay(2000);
}
