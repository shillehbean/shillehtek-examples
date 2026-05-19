# Toggles the laser on and off every 0.5 seconds using a Raspberry Pi GPIO pin (BCM 17) to drive a transistor that switches the laser power.
#
# Buy this module: https://shillehtek.com/products/shillehtek-6mm-650nm-5mw-red-laser-diode-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-6mm-650nm-5mw-red-laser-diode-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Laser Diode - On/Off via transistor on BCM 17

import RPi.GPIO as GPIO
import time

LASER_PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(LASER_PIN, GPIO.OUT)

try:
    while True:
        GPIO.output(LASER_PIN, GPIO.HIGH)   # ON
        time.sleep(0.5)
        GPIO.output(LASER_PIN, GPIO.LOW)    # OFF
        time.sleep(0.5)
except KeyboardInterrupt:
    GPIO.cleanup()
