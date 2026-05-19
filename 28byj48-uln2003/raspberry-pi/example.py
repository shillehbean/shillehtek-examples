# Controls the 28BYJ-48 from a Raspberry Pi using RPi.GPIO in an 8-step half-step sequence to rotate one full revolution clockwise and counterclockwise.
#
# Buy this module: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 28BYJ-48 + ULN2003 - Raspberry Pi half-step example
# IN1->GPIO 17, IN2->GPIO 27, IN3->GPIO 22, IN4->GPIO 23

import RPi.GPIO as GPIO
import time

PINS = [17, 27, 22, 23]  # IN1, IN2, IN3, IN4

# 8-step half-stepping sequence for smoother motion
HALF_STEP = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1],
]

GPIO.setmode(GPIO.BCM)
for pin in PINS:
    GPIO.setup(pin, GPIO.OUT)
    GPIO.output(pin, 0)

def step(direction=1, steps=4096, delay_s=0.001):
    seq = HALF_STEP if direction > 0 else list(reversed(HALF_STEP))
    for i in range(steps):
        for pin, val in zip(PINS, seq[i % 8]):
            GPIO.output(pin, val)
        time.sleep(delay_s)

try:
    print("Rotating one full revolution clockwise...")
    step(direction=1, steps=4096)  # 4096 = one revolution in half-step mode
    time.sleep(1)
    print("Rotating one full revolution counter-clockwise...")
    step(direction=-1, steps=4096)
finally:
    for pin in PINS:
        GPIO.output(pin, 0)
    GPIO.cleanup()
