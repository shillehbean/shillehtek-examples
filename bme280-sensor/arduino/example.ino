// Reads temperature, humidity, and pressure from a BME280 over I2C using the Adafruit BME280 library and prints the values to Serial every second.
//
// Buy this module: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bme280-environmental-sensor-raspberry-pi-arduino-esp32-i2c-humidity-pressure-and-temperature-measurement
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BME280 - Read temperature, humidity, and pressure
// Requires: Adafruit BME280 Library + Adafruit Unified Sensor

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // 0x76 is default; try 0x77 if SDO is tied to VCC
  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME280 sensor. Check wiring!");
    while (1);
  }
  Serial.println("BME280 ready.");
}

void loop() {
  Serial.print("Temp: ");
  Serial.print(bme.readTemperature());
  Serial.println(" *C");

  Serial.print("Humidity: ");
  Serial.print(bme.readHumidity());
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println();
  delay(1000);
}
