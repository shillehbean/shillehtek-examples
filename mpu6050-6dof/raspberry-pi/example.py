# Uses the mpu6050 Python package on a Raspberry Pi to read accelerometer, gyroscope, and temperature data over I2C and print the values in a loop (0.5 s interval).
#
# Buy this module: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu6050-accelerometer-6dof-raspberry-pi-arduino-esp32-i2c-accelerometer
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MPU6050 IMU - Raspberry Pi Example
# Install: pip3 install mpu6050-raspberrypi
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

from mpu6050 import mpu6050
import time

sensor = mpu6050(0x68)

print("MPU6050 IMU (Ctrl+C to stop)")

try:
    while True:
        accel = sensor.get_accel_data()     # m/s^2
        gyro  = sensor.get_gyro_data()      # deg/s
        temp  = sensor.get_temp()           # deg C

        print("Accel  X={:+.2f}  Y={:+.2f}  Z={:+.2f}".format(
            accel['x'], accel['y'], accel['z']))
        print("Gyro   X={:+.2f}  Y={:+.2f}  Z={:+.2f}".format(
            gyro['x'],  gyro['y'],  gyro['z']))
        print("Temp   {:.2f} C\n".format(temp))
        time.sleep(0.5)
except KeyboardInterrupt:
    print("\nStopped by user")
