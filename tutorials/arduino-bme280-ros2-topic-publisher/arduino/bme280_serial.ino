// Arduino sketch that reads temperature, humidity, and pressure from a BME280 over I2C and prints CSV (temp,hum,press) to Serial every 2 seconds.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-bme280-ros2-topic-publisher
// Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!bme.begin(0x76)) {
    Serial.println("BME280 not found!");
    while (1);
  }

  Serial.println("BME280 found.");
}

void loop() {
  float temp = bme.readTemperature();
  float hum = bme.readHumidity();
  float pres = bme.readPressure() / 100.0F;

  Serial.print(temp);
  Serial.print(",");
  Serial.print(hum);
  Serial.print(",");
  Serial.println(pres);

  delay(2000);
}
