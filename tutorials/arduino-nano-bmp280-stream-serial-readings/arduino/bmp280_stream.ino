// Reads temperature, pressure, and altitude from a BMP280 over I2C and prints the values to the Serial Monitor once per second.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-bmp280-stream-serial-readings
// Parts used: https://shillehtek.com/products/shillehtek-bmp280-pre-soldered
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found at 0x76, trying 0x77...");
    if (!bmp.begin(0x77)) { Serial.println("BMP280 still not found"); while (1); }
  }
}

void loop() {
  Serial.print("T="); Serial.print(bmp.readTemperature(), 1);
  Serial.print(" C  P="); Serial.print(bmp.readPressure() / 100.0, 1);
  Serial.print(" hPa  Alt="); Serial.print(bmp.readAltitude(1013.25), 1);
  Serial.println(" m");
  delay(1000);
}
