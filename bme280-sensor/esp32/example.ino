// Initializes I2C on an ESP32 (GPIO21 SDA, GPIO22 SCL), reads temperature, humidity, and pressure from a BME280 using the Adafruit library, and prints formatted values repeatedly.
//
// Buy this module: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bme280-environmental-sensor-raspberry-pi-arduino-esp32-i2c-humidity-pressure-and-temperature-measurement
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BME280 on ESP32 via I2C (GPIO21 SDA, GPIO22 SCL)
// Requires: Adafruit BME280 Library

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22); // SDA, SCL

  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found. Check wiring/address.");
    while (1);
  }
  Serial.println("BME280 ready.");
}

void loop() {
  Serial.printf("Temp: %.2f C | Humidity: %.2f %% | Pressure: %.2f hPa\n",
                bme.readTemperature(),
                bme.readHumidity(),
                bme.readPressure() / 100.0F);
  delay(1000);
}
