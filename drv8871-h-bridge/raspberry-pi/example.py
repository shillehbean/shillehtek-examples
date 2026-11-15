# Raspberry Pi (gpiozero) script that runs a DC motor forward, stops (coasts), and reverses at variable speeds using the DRV8871.
#
# Buy this module: https://shillehtek.com/products/drv8871-h-bridge-motor-driver-module-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/drv8871-h-bridge-motor-driver-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# DRV8871 motor driver on Raspberry Pi - forward, stop, reverse with gpiozero
# Wiring: IN1 = GPIO 17 (pin 11), IN2 = GPIO 27 (pin 13), GND = pin 6
# The motor supply (6.5 V to 45 V) goes to POWER + and POWER -. Leave the header VM pin unconnected.
from gpiozero import Motor
from time import sleep

motor = Motor(forward=17, backward=27)     # PWM speed control on both inputs

while True:
    motor.forward(0.5)      # half speed forward
    sleep(2)
    motor.forward(1.0)      # full speed forward
    sleep(2)
    motor.stop()            # both inputs low = coast
    sleep(1)
    motor.backward(0.5)     # half speed in reverse
    sleep(2)
    motor.stop()
    sleep(2)
