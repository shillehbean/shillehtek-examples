// Sets calibrated gyro and accelerometer offset values on the MPU6050 instance to improve angle accuracy.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-mpu6050-accurate-angle-readings
// Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
//             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// supply your own gyro offsets here, scaled for min sensitivity
mpu.setXGyroOffset(11);
mpu.setYGyroOffset(-51);
mpu.setZGyroOffset(-19);
mpu.setZAccelOffset(2048); // 1688 factory default for my test chip
