// Reads temperature and pressure from an Adafruit BMP085/BMP180 sensor and prints JSON-formatted readings over Serial every 2 seconds.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-bmp180-real-time-dashboard
// Parts used: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;

void setup() {
  Serial.begin(9600);
  if (!bmp.begin()) {
    Serial.println("Sensor not found!");
    while (1);
  }
}

void loop() {
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0;

  Serial.print("{\"temp\":");
  Serial.print(temp);
  Serial.print(",\"pressure\":");
  Serial.print(pressure);
  Serial.println("}");

  delay(2000);
}
