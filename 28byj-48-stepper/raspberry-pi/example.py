# Python (RPi.GPIO) script for Raspberry Pi that steps the 28BYJ-48 using a half-step sequence for one full revolution in each direction and performs GPIO cleanup on exit.
#
# Buy this module: https://shillehtek.com/products/stepper-motor-28byj-48-5v-arduino-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/stepper-motor-28byj-48-5v-arduino-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 28BYJ-48 + ULN2003 - Raspberry Pi Example (half-step)
# IN1->GPIO17, IN2->GPIO18, IN3->GPIO27, IN4->GPIO22

import RPi.GPIO as GPIO
import time

PINS = [17, 18, 27, 22]
HALF_STEP = [
    (1,0,0,0), (1,1,0,0), (0,1,0,0), (0,1,1,0),
    (0,0,1,0), (0,0,1,1), (0,0,0,1), (1,0,0,1),
]
STEPS_PER_REV = 4096

GPIO.setmode(GPIO.BCM)
for p in PINS:
    GPIO.setup(p, GPIO.OUT, initial=0)

def move(steps, delay=0.0012):
    seq = HALF_STEP if steps > 0 else HALF_STEP[::-1]
    for i in range(abs(steps)):
        for pin, v in zip(PINS, seq[i % 8]):
            GPIO.output(pin, v)
        time.sleep(delay)
    for p in PINS:
        GPIO.output(p, 0)            # release coils

try:
    while True:
        print("One revolution clockwise...")
        move(STEPS_PER_REV)
        time.sleep(1)
        print("One revolution counter-clockwise...")
        move(-STEPS_PER_REV)
        time.sleep(1)
except KeyboardInterrupt:
    GPIO.cleanup()
    print("Stopped by user")
