# Uses gpiozero with the pigpio backend on a Raspberry Pi to sweep the MG90S smoothly between 0–180° by specifying the pulse width range for the servo.
#
# Buy this module: https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# MG90S Servo - Raspberry Pi Example using gpiozero
# Signal pin: GPIO 18 (physical pin 12)
# Power the servo from a separate 5V supply, share ground with the Pi.
#
# For smoothest motion, run pigpiod first:
#   sudo pigpiod
# Then run this script.

from gpiozero import AngularServo
from gpiozero.pins.pigpio import PiGPIOFactory
from time import sleep

# Use pigpio backend for jitter-free PWM
factory = PiGPIOFactory()

servo = AngularServo(
    18,
    min_angle=0,
    max_angle=180,
    min_pulse_width=0.0005,   # 500 us
    max_pulse_width=0.0024,   # 2400 us
    pin_factory=factory,
)

try:
    while True:
        for angle in range(0, 181, 2):
            servo.angle = angle
            sleep(0.015)
        for angle in range(180, -1, -2):
            servo.angle = angle
            sleep(0.015)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    servo.detach()
