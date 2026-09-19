# Demonstrates using a MicroPython ADXL345 driver over I2C to read and print X/Y/Z acceleration on a microcontroller (e.g., Pico) at ~100 ms intervals.
#
# Buy this module: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/adxl345-accelerometer-3dof-raspberry-pi-arduino-esp32-i2c-accelerometer-klipper-tuning
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ADXL345 - Pico MicroPython
# Library: micropython-adxl345 from PyPI or copy adxl345.py manually.

from machine import Pin, I2C
import adxl345
import time

i2c = I2C(0, scl=Pin(5), sda=Pin(4), freq=400_000)
accel = adxl345.ADXL345(i2c)

while True:
    x, y, z = accel.x, accel.y, accel.z
    print("X={:6.2f}  Y={:6.2f}  Z={:6.2f}".format(x, y, z))
    time.sleep_ms(100)
