# Connects to an MPU6050 over I2C, reads the accelerometer X axis, applies an exponential low-pass filter, and prints the raw and filtered values at 10 Hz.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-mpu6050-smooth-sensor-data
# Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
#             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#Native libs
from machine import Pin, I2C
import math
import time
from time import sleep

from imu import MPU6050


i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
sensor = MPU6050(i2c)
filtered_ax = 0
alpha = 0.85 # must be between 0 and 1 inclusive


def low_pass_filter(prev_value, new_value):
    return alpha * prev_value + (1 - alpha) * new_value


while True:
    ax_new = sensor.accel.x
    filtered_ax = low_pass_filter(filtered_ax, ax_new)
    print("filtered_ax: ", filtered_ax, "raw ax", ax_new)
    time.sleep(1/10)
