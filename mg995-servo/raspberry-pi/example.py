# Raspberry Pi Python example (gpiozero + pigpio) that controls an AngularServo on GPIO18 with 0.5–2.5 ms pulse widths and sweeps between -90° and +90°.
#
# Buy this module: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Run pigpiod first:  sudo pigpiod
# pip install gpiozero pigpio

from gpiozero import AngularServo
from gpiozero.pins.pigpio import PiGPIOFactory
import time

servo = AngularServo(
    18,
    min_pulse_width=0.0005,   # 0.5 ms
    max_pulse_width=0.0025,   # 2.5 ms
    pin_factory=PiGPIOFactory()
)

while True:
    for a in (-90, 0, 90, 0):
        servo.angle = a
        time.sleep(0.6)
