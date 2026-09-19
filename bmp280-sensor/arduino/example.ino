// Reads temperature, pressure, and estimated altitude from a BMP280 over I2C and prints the values to the Arduino Serial console.
//
// Buy this module: https://shillehtek.com/products/shillehtek-bmp280-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bmp280-i2c-iic-digital-atmospheric-pressure-temperature-altitude-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// BMP280 Pressure & Temperature Sensor - Arduino Example
// Library: Adafruit BMP280 Library (Library Manager)

#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {   // Default address; try 0x77 if 0x76 fails
    Serial.println("BMP280 not found!");
    while (1) {}
  }

  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,    // temperature
                  Adafruit_BMP280::SAMPLING_X16,   // pressure
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  Serial.print("Temp: ");      Serial.print(bmp.readTemperature()); Serial.println(" C");
  Serial.print("Pressure: ");  Serial.print(bmp.readPressure() / 100.0F); Serial.println(" hPa");
  Serial.print("Altitude: ");  Serial.print(bmp.readAltitude(1013.25)); Serial.println(" m");
  Serial.println();
  delay(1000);
}
