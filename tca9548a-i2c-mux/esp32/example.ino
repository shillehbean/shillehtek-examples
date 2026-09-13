// Selects TCA9548A channels 0 and 1 to access two BME280 sensors that share the same I2C address and prints each channel's temperature readings.
//
// Buy this module: https://shillehtek.com/products/Arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-9548-tca9548a-1-to-8-i2c-8-channel-multiplexer-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_BME280.h>

#define TCA_ADDR 0x70
Adafruit_BME280 bme;

void tcaSelect(uint8_t ch) {
  Wire.beginTransmission(TCA_ADDR);
  Wire.write(1 << ch);
  Wire.endTransmission();
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  tcaSelect(0);
  if (!bme.begin(0x76)) Serial.println("BME on ch0 not found");

  tcaSelect(1);
  if (!bme.begin(0x76)) Serial.println("BME on ch1 not found");
}

void loop() {
  tcaSelect(0);
  Serial.printf("Ch0: %.2f C\n", bme.readTemperature());
  tcaSelect(1);
  Serial.printf("Ch1: %.2f C\n", bme.readTemperature());
  delay(1000);
}
