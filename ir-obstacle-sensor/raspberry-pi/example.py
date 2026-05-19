# Reads the IR sensor on GPIO17 using RPi.GPIO, printing obstacle status in a loop and cleaning up GPIO on Ctrl-C.
#
# Buy this module: https://shillehtek.com/products/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# IR Obstacle Sensor on Raspberry Pi - print state and trigger an action

import RPi.GPIO as GPIO
import time

PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(PIN, GPIO.IN)

try:
    while True:
        if GPIO.input(PIN) == 0:
            print("Obstacle detected!")
        else:
            print("Path clear")
        time.sleep(0.1)
except KeyboardInterrupt:
    GPIO.cleanup()
