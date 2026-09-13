// Reads X, Y, Z acceleration from an ADXL345 using the Adafruit library and streams the values over Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-adxl345-stream-3-axis-acceleration
// Parts used: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  if (!accel.begin()) { Serial.println("ADXL345 not found"); while (1); }
  accel.setRange(ADXL345_RANGE_4_G);
}

void loop() {
  sensors_event_t e;
  accel.getEvent(&e);
  Serial.print("X="); Serial.print(e.acceleration.x, 2);
  Serial.print(" Y="); Serial.print(e.acceleration.y, 2);
  Serial.print(" Z="); Serial.print(e.acceleration.z, 2);
  Serial.println(" m/s^2");
  delay(200);
}
