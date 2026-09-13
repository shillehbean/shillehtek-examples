// Initializes the MPU6050, verifies the connection, and continuously reads and prints raw accelerometer and gyroscope values over Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/stm32-blue-pill-mpu6050-gyro-calibration
// Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
//             https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f103c8t6-arm-stm32
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Initialize MPU6050
  Serial.println("Initializing MPU6050...");
  mpu.initialize();

  // Check if the MPU6050 is connected
  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful");
  } else {
    Serial.println("MPU6050 connection failed");
    while (1); // Halt the program if MPU6050 is not connected
  }
}

void loop() {
  // Variables to hold the raw data
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  // Read raw accelerometer and gyroscope data
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Print accelerometer raw values
  Serial.print("Accel X: "); Serial.print(ax);
  Serial.print(" | Accel Y: "); Serial.print(ay);
  Serial.print(" | Accel Z: "); Serial.println(az);

  // Print gyroscope raw values
  Serial.print("Gyro X: "); Serial.print(gx);
  Serial.print(" | Gyro Y: "); Serial.print(gy);
  Serial.print(" | Gyro Z: "); Serial.println(gz);

  delay(100); // Delay for readability
}
