// Initializes I2C on an ESP32 (GPIO21 SDA, GPIO22 SCL), reads the MPU9250, and prints computed roll, pitch, and yaw values to Serial in a 20 ms loop.
//
// Buy this module: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu9250-authentic-gy-9250-pre-soldered-9-axis-9-dof-accelerometer-magnetometer
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MPU9250 on ESP32 via I2C (GPIO21 SDA, GPIO22 SCL)

#include <MPU9250.h>

MPU9250 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  delay(100);
  if (!mpu.setup(0x68)) {
    Serial.println("MPU9250 not found.");
    while (1);
  }
}

void loop() {
  if (mpu.update()) {
    Serial.printf("Roll=%.2f Pitch=%.2f Yaw=%.2f\n",
                  mpu.getRoll(), mpu.getPitch(), mpu.getYaw());
  }
  delay(20);
}
