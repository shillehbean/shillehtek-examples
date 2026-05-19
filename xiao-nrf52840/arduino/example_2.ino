// Creates a BLE peripheral advertising the standard Battery Service and updates/notifies a battery level characteristic every 5 seconds.
//
// Buy this module: https://shillehtek.com/products/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-nrf52840-pre-soldered-with-usb-c-cable-manual
// More examples: https://github.com/shillehtek/examples
//

// XIAO nRF52840 - BLE peripheral advertising a Battery service
// Library: ArduinoBLE (Library Manager). Connect with nRF Connect on your phone.

#include <ArduinoBLE.h>

BLEService batteryService("180F");
BLEUnsignedCharCharacteristic batteryLevel("2A19", BLERead | BLENotify);

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 3000) {}

  if (!BLE.begin()) {
    Serial.println("BLE init failed!");
    while (1) {}
  }

  BLE.setLocalName("ShillehTek-XIAO");
  BLE.setAdvertisedService(batteryService);
  batteryService.addCharacteristic(batteryLevel);
  BLE.addService(batteryService);
  batteryLevel.writeValue(100);

  BLE.advertise();
  Serial.println("Advertising as ShillehTek-XIAO");
}

void loop() {
  BLE.poll();

  static uint8_t level = 100;
  static unsigned long t = 0;
  if (millis() - t > 5000) {
    t = millis();
    level = (level > 0) ? level - 1 : 100;
    batteryLevel.writeValue(level);
    Serial.print("Battery: "); Serial.println(level);
  }
}
