# Uses Adafruit CircuitPython ServoKit to control the PCA9685 and smoothly sweep a servo connected to channel 0 through 0–180° on a single-board Linux/Python environment.
#
# Buy this module: https://shillehtek.com/products/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pca9685-16-channel-12-bit-pwm-servo-motor-driver-i2c-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: sudo pip3 install adafruit-circuitpython-pca9685 adafruit-circuitpython-servokit

from adafruit_servokit import ServoKit
import time

kit = ServoKit(channels=16)

while True:
    for angle in range(0, 181, 5):
        kit.servo[0].angle = angle
        time.sleep(0.02)
    for angle in range(180, -1, -5):
        kit.servo[0].angle = angle
        time.sleep(0.02)
