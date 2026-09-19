// Reads raw accelerometer, gyroscope, and magnetometer axis values from the MPU9250 using the hideakitai MPU9250 Arduino library and prints them over Serial every 100 ms.
//
// Buy this module: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu9250-authentic-gy-9250-pre-soldered-9-axis-9-dof-accelerometer-magnetometer
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MPU9250 - Read accel, gyro, and mag (9 axes)
// Requires: MPU9250 library by hideakitai

#include <MPU9250.h>

MPU9250 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(100);

  if (!mpu.setup(0x68)) {
    Serial.println("MPU9250 not found. Check wiring.");
    while (1);
  }
  Serial.println("MPU9250 ready.");
}

void loop() {
  if (mpu.update()) {
    Serial.print("Ax: "); Serial.print(mpu.getAccX());
    Serial.print(" Ay: "); Serial.print(mpu.getAccY());
    Serial.print(" Az: "); Serial.println(mpu.getAccZ());

    Serial.print("Gx: "); Serial.print(mpu.getGyroX());
    Serial.print(" Gy: "); Serial.print(mpu.getGyroY());
    Serial.print(" Gz: "); Serial.println(mpu.getGyroZ());

    Serial.print("Mx: "); Serial.print(mpu.getMagX());
    Serial.print(" My: "); Serial.print(mpu.getMagY());
    Serial.print(" Mz: "); Serial.println(mpu.getMagZ());
    Serial.println();
  }
  delay(100);
}
