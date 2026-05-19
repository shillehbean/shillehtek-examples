# Operate the SG92R from a Raspberry Pi using gpiozero with the pigpio backend on GPIO18, moving to minimum, mid, and maximum positions via specified pulse widths.
#
# Buy this module: https://shillehtek.com/products/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# SG92R Servo - Raspberry Pi Python Example
# Install: sudo pip3 install gpiozero pigpio
# Run pigpiod first: sudo pigpiod

from gpiozero import Servo
from gpiozero.pins.pigpio import PiGPIOFactory
import time

factory = PiGPIOFactory()
servo = Servo(18, pin_factory=factory,
              min_pulse_width=0.0005, max_pulse_width=0.0024)

while True:
    servo.min()
    time.sleep(1)
    servo.mid()
    time.sleep(1)
    servo.max()
    time.sleep(1)
