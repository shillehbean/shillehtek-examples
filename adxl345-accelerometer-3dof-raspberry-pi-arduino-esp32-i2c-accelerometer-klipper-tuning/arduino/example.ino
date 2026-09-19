// Initializes the ADXL345 using the Adafruit_ADXL345 library, sets the ±16 g range, and prints X/Y/Z acceleration in m/s^2 over the serial port every 100 ms.
//
// Buy this module: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/adxl345-accelerometer-3dof-raspberry-pi-arduino-esp32-i2c-accelerometer-klipper-tuning
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ADXL345 - Read X/Y/Z acceleration
// Library: Adafruit ADXL345 (Library Manager) — pulls in Adafruit Unified Sensor

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  if (!accel.begin()) {
    Serial.println("ADXL345 not detected!");
    while (1) {}
  }
  accel.setRange(ADXL345_RANGE_16_G);
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" m/s^2  ");
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" m/s^2  ");
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.println(" m/s^2");
  delay(100);
}
