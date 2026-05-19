# Runs a half-step full-revolution example for the 28BYJ-48 on a Raspberry Pi Pico (MicroPython) using machine.Pin to toggle the motor coils.
#
# Buy this module: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver-manual
# More examples: https://github.com/shillehtek/examples
#

# 28BYJ-48 + ULN2003 - Pico MicroPython half-step example
# IN1->GP2, IN2->GP3, IN3->GP4, IN4->GP5

from machine import Pin
import time

pins = [Pin(2, Pin.OUT), Pin(3, Pin.OUT), Pin(4, Pin.OUT), Pin(5, Pin.OUT)]

HALF_STEP = [
    (1, 0, 0, 0),
    (1, 1, 0, 0),
    (0, 1, 0, 0),
    (0, 1, 1, 0),
    (0, 0, 1, 0),
    (0, 0, 1, 1),
    (0, 0, 0, 1),
    (1, 0, 0, 1),
]

def step(direction=1, steps=4096, delay_ms=2):
    seq = HALF_STEP if direction > 0 else tuple(reversed(HALF_STEP))
    for i in range(steps):
        pattern = seq[i % 8]
        for pin, val in zip(pins, pattern):
            pin.value(val)
        time.sleep_ms(delay_ms)

try:
    print("One full revolution clockwise")
    step(direction=1, steps=4096)
    time.sleep(1)
    print("One full revolution counter-clockwise")
    step(direction=-1, steps=4096)
finally:
    for p in pins:
        p.value(0)
