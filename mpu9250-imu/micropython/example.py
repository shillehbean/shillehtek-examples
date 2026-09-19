# Runs on a MicroPython board (e.g., Raspberry Pi Pico) to scan I2C, instantiate an MPU9250 driver, and print acceleration, gyro, and magnetometer vectors every 0.5 seconds.
#
# Buy this module: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mpu9250-authentic-gy-9250-pre-soldered-9-axis-9-dof-accelerometer-magnetometer
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MPU9250 on Pico via I2C0 (GP0 SDA, GP1 SCL)
# Upload mpu9250.py and ak8963.py driver files to the Pico first.

from machine import I2C, Pin
from mpu9250 import MPU9250
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
print("I2C scan:", [hex(d) for d in i2c.scan()])

sensor = MPU9250(i2c)

while True:
    print("Accel:", sensor.acceleration)
    print("Gyro :", sensor.gyro)
    print("Mag  :", sensor.magnetic)
    print("-" * 30)
    time.sleep(0.5)
