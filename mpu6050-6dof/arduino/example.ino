// Initializes the MPU6050 using the Adafruit_MPU6050 library, configures accelerometer/gyro ranges and filter bandwidth, then prints accelerometer, gyro, and temperature readings to the Serial console every 500 ms.
//
// Buy this module: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu6050-accelerometer-6dof-raspberry-pi-arduino-esp32-i2c-accelerometer
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MPU6050 IMU - Arduino Example
// Library: "Adafruit MPU6050" (Arduino Library Manager)
// I2C: SDA -> A4, SCL -> A5

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not found. Check wiring.");
    while (1) delay(10);
  }
  Serial.println("MPU6050 ready.");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop() {
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  Serial.print("Accel (m/s^2)  X="); Serial.print(a.acceleration.x);
  Serial.print(" Y="); Serial.print(a.acceleration.y);
  Serial.print(" Z="); Serial.println(a.acceleration.z);

  Serial.print("Gyro  (rad/s)  X="); Serial.print(g.gyro.x);
  Serial.print(" Y="); Serial.print(g.gyro.y);
  Serial.print(" Z="); Serial.println(g.gyro.z);

  Serial.print("Temp  (C)      "); Serial.println(t.temperature);
  Serial.println();
  delay(500);
}
