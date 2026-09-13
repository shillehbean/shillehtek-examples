// Reads temperature from a BME280 sensor over I2C and publishes it via BLE using the Environmental Sensing Service (UUID 181A) and the temperature characteristic (UUID 2A6E) as a 16-bit value in hundredths of degrees Celsius.
//
// Full tutorial: https://shillehtek.com/blogs/news/xiao-nrf52840-bme280-ble-temperature-humidity
// Parts used: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
//             https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable
//             https://shillehtek.com/products/shillehtek-dht22-with-cables
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <bluefruit.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;
BLEService envSvc("181A");                       // Environmental Sensing
BLECharacteristic tempC("2A6E", BLECharacteristic::READ);

void setup() {
  Wire.begin();
  bme.begin(0x76);
  Bluefruit.begin();
  Bluefruit.setName("XIAO-Env");
  envSvc.begin();
  tempC.setProperties(CHR_PROPS_READ | CHR_PROPS_NOTIFY);
  tempC.setFixedLen(2);
  tempC.begin();
  Bluefruit.Advertising.addService(envSvc);
  Bluefruit.Advertising.start(0);
}

void loop() {
  int16_t t = (int16_t)(bme.readTemperature() * 100);
  tempC.write((uint8_t*)&t, 2);
  delay(5000);
}
