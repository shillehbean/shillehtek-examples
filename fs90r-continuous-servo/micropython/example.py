# MicroPython example for a Pico (or other RP2040) that uses PWM with duty in microseconds to control the FS90R's continuous rotation direction and speed.
#
# Buy this module: https://shillehtek.com/products/fs90r-micro-servo-continuous-rotation
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fs90r-micro-servo-continuous-rotation-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# FS90R continuous rotation servo on Raspberry Pi Pico (MicroPython)
# Wiring: orange = GP15, red = VBUS (5 V), brown = GND
from machine import Pin, PWM
import time

servo = PWM(Pin(15))
servo.freq(50)                 # one pulse every 20 ms

STOP_US = 1500                 # change by a few microseconds if the servo creeps at stop


def pulse(us):
    servo.duty_ns(us * 1000)


while True:
    pulse(STOP_US - 200)       # clockwise; go further from 1500 for more speed
    time.sleep(2)
    pulse(STOP_US)             # stop
    time.sleep(1)
    pulse(STOP_US + 200)       # counterclockwise
    time.sleep(2)
    pulse(STOP_US)             # stop
    time.sleep(1)
