// Initializes the MPU6050, runs a gyroscope calibration routine to compute offsets, then reads sensor data and applies the gyro offsets before printing adjusted values.
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

int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t gyroXOffset = 0, gyroYOffset = 0, gyroZOffset = 0;

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

  // Calibrate gyroscope
  Serial.println("Calibrating gyroscope... Please keep the sensor steady.");
  calibrateGyro();
  Serial.println("Calibration complete.");
}

void loop() {
  // Read raw accelerometer and gyroscope data
  mpu.getAcceleration(&ax, &ay, &az);
  mpu.getRotation(&gx, &gy, &gz);

  // Subtract the gyro offsets from the raw values
  gx -= gyroXOffset;
  gy -= gyroYOffset;
  gz -= gyroZOffset;

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

void calibrateGyro() {
  int32_t gyroXSum = 0, gyroYSum = 0, gyroZSum = 0;
  const int numReadings = 1000;

  for (int i = 0; i < numReadings; i++) {
    mpu.getRotation(&gx, &gy, &gz);
    gyroXSum += gx;
    gyroYSum += gy;
    gyroZSum += gz;
    delay(3); // Delay to allow for a reasonable calibration time
  }

  // Calculate the average offsets
  gyroXOffset = gyroXSum / numReadings;
  gyroYOffset = gyroYSum / numReadings;
  gyroZOffset = gyroZSum / numReadings;

  Serial.print("Gyro X Offset: "); Serial.println(gyroXOffset);
  Serial.print("Gyro Y Offset: "); Serial.println(gyroYOffset);
  Serial.print("Gyro Z Offset: "); Serial.println(gyroZOffset);
}
