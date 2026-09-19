# MicroPython example for ESP32 that drives the 28BYJ-48 in half-step mode to perform one full revolution clockwise and counter-clockwise, with coil release after motion.
#
# Buy this module: https://shillehtek.com/products/stepper-motor-28byj-48-5v-arduino-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/stepper-motor-28byj-48-5v-arduino-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 28BYJ-48 + ULN2003 - ESP32 MicroPython Example (half-step)
# IN1->GPIO 14, IN2->GPIO 27, IN3->GPIO 26, IN4->GPIO 25

from machine import Pin
import time

pins = [Pin(p, Pin.OUT) for p in (14, 27, 26, 25)]

HALF_STEP = [
    (1,0,0,0), (1,1,0,0), (0,1,0,0), (0,1,1,0),
    (0,0,1,0), (0,0,1,1), (0,0,0,1), (1,0,0,1),
]
STEPS_PER_REV = 4096                  # half-steps per output rev

def move(steps, delay_us=1200):
    seq = HALF_STEP if steps > 0 else HALF_STEP[::-1]
    for i in range(abs(steps)):
        for pin, v in zip(pins, seq[i % 8]):
            pin.value(v)
        time.sleep_us(delay_us)
    for pin in pins:                  # release coils (no heat)
        pin.value(0)

while True:
    print("One revolution clockwise...")
    move(STEPS_PER_REV)
    time.sleep(1)
    print("One revolution counter-clockwise...")
    move(-STEPS_PER_REV)
    time.sleep(1)
