# MicroPython example for the Raspberry Pi Pico that pulses STEP and DIR GPIOs with microsecond timing to drive the stepper forward and back using 16x microstepping.
#
# Buy this module: https://shillehtek.com/products/shillehtek-original-a4988-stepper-motor-driver-with-heatsink
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-original-a4988-stepper-motor-driver-with-heatsink-manual
# More examples: https://github.com/shillehtek/examples
#

# A4988 - Pico MicroPython
# STEP = GP15, DIR = GP14

from machine import Pin
import time

step = Pin(15, Pin.OUT)
direction = Pin(14, Pin.OUT)

def step_motor(steps, dir_value, delay_us=500):
    direction.value(dir_value)
    for _ in range(steps):
        step.value(1)
        time.sleep_us(delay_us)
        step.value(0)
        time.sleep_us(delay_us)

while True:
    step_motor(3200, 1)   # forward 1 rev (16x microstepping)
    time.sleep(0.5)
    step_motor(3200, 0)   # reverse
    time.sleep(0.5)
