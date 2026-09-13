// Starts the Adafruit Bluefruit BLE stack, sets the device name and TX power, and begins advertising indefinitely.
//
// Full tutorial: https://shillehtek.com/blogs/news/xiao-nrf52840-bme280-ble-temperature-humidity
// Parts used: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <bluefruit.h>

void setup() {
  Serial.begin(115200);
  Bluefruit.begin();
  Bluefruit.setName("ShillehTek-XIAO");
  Bluefruit.setTxPower(0);
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.start(0);
  Serial.println("Advertising");
}

void loop() {}
