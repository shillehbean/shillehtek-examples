// Reads accelerometer, gyroscope, and magnetometer data from an MPU9250 and prints formatted 9-axis values to Serial at 115200 baud.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mpu9250-stream-9-axis-data
// Parts used: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <MPU9250.h>

MPU9250 imu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(2000);
  imu.setup(0x68);
}

void loop() {
  if (imu.update()) {
    Serial.print("aX="); Serial.print(imu.getAccX(), 2);
    Serial.print(" aY="); Serial.print(imu.getAccY(), 2);
    Serial.print(" aZ="); Serial.print(imu.getAccZ(), 2);
    Serial.print(" | gX="); Serial.print(imu.getGyroX(), 2);
    Serial.print(" gY="); Serial.print(imu.getGyroY(), 2);
    Serial.print(" gZ="); Serial.print(imu.getGyroZ(), 2);
    Serial.print(" | mX="); Serial.print(imu.getMagX(), 2);
    Serial.print(" mY="); Serial.print(imu.getMagY(), 2);
    Serial.print(" mZ="); Serial.println(imu.getMagZ(), 2);
  }
  delay(50);
}
