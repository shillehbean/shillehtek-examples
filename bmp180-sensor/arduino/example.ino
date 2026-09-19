// Reads temperature and pressure from a BMP180 using the Adafruit BMP085 Unified library and prints temperature, pressure, and computed altitude to the Serial console every second.
//
// Buy this module: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bmp180-i2c-iic-digital-atmospheric-pressure-temperature-altitude-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BMP180 - Arduino Example
// Library: Adafruit BMP085 Unified library (works for BMP085 and BMP180)

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("BMP180 not found!");
    while (1) {}
  }
}

void loop() {
  sensors_event_t event;
  bmp.getEvent(&event);

  if (event.pressure) {
    Serial.print("Pressure: "); Serial.print(event.pressure); Serial.println(" hPa");

    float temperature;
    bmp.getTemperature(&temperature);
    Serial.print("Temp: "); Serial.print(temperature); Serial.println(" C");

    float seaLevelPressure = 1013.25;
    Serial.print("Altitude: ");
    Serial.print(bmp.pressureToAltitude(seaLevelPressure, event.pressure));
    Serial.println(" m");
  }
  Serial.println();
  delay(1000);
}
