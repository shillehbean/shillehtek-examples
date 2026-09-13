// Reads accelerometer and gyroscope events from an MPU6050 using the Adafruit_MPU6050 library and prints the values over Serial at 10 Hz.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mpu6050-stream-accel-gyro
// Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  if (!mpu.begin()) {
    Serial.println("MPU6050 not found!");
    while (1) delay(10);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);
  Serial.print("aX=");  Serial.print(a.acceleration.x, 2);
  Serial.print(" aY="); Serial.print(a.acceleration.y, 2);
  Serial.print(" aZ="); Serial.print(a.acceleration.z, 2);
  Serial.print(" | gX=");  Serial.print(g.gyro.x, 2);
  Serial.print(" gY="); Serial.print(g.gyro.y, 2);
  Serial.print(" gZ="); Serial.println(g.gyro.z, 2);
  delay(100);
}
