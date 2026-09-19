# Uses Adafruit CircuitPython on a Raspberry Pi to enable proximity and gesture detection on the APDS-9960 and prints detected swipe directions in a continuous loop.
#
# Buy this module: https://shillehtek.com/products/apds-9960-gesture-proximity-color-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/apds-9960-gesture-proximity-color-sensor-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# APDS-9960 Gesture Sensor - Raspberry Pi Example
# SDA: Pin 3 (GPIO 2), SCL: Pin 5 (GPIO 3), VCC: Pin 1 (3.3V)
#
# Setup:
#   sudo raspi-config          (Interface Options - enable I2C)
#   pip3 install adafruit-circuitpython-apds9960

import time
import board
import busio
from adafruit_apds9960.apds9960 import APDS9960

# Create the I2C bus and the sensor object (address 0x39)
i2c = busio.I2C(board.SCL, board.SDA)
sensor = APDS9960(i2c)

# The gesture engine needs the proximity engine running as well
sensor.enable_proximity = True
sensor.enable_gesture = True

# gesture() returns 0 = none, 1 = up, 2 = down, 3 = left, 4 = right
names = {1: "UP", 2: "DOWN", 3: "LEFT", 4: "RIGHT"}

print("Swipe a hand 5-15 cm over the sensor (Ctrl+C to stop)...")

try:
    while True:
        gesture = sensor.gesture()
        if gesture:
            print("Gesture:", names.get(gesture, "UNKNOWN"))
        time.sleep(0.05)
except KeyboardInterrupt:
    print("Stopped by user")
