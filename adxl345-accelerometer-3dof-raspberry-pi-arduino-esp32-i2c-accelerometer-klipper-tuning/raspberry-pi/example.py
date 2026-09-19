# Uses CircuitPython on a Raspberry Pi to read acceleration from the ADXL345 over I2C and print X/Y/Z values in m/s^2 every 0.1 seconds.
#
# Buy this module: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/adxl345-accelerometer-3dof-raspberry-pi-arduino-esp32-i2c-accelerometer-klipper-tuning
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# ADXL345 - Raspberry Pi Python Example
# Install: sudo pip3 install adafruit-circuitpython-adxl34x

import time
import board
import adafruit_adxl34x

i2c = board.I2C()
accel = adafruit_adxl34x.ADXL345(i2c)

while True:
    x, y, z = accel.acceleration
    print(f"X: {x:6.2f}  Y: {y:6.2f}  Z: {z:6.2f}  m/s^2")
    time.sleep(0.1)
