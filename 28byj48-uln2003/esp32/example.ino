// Runs a continuous full-step rotation example for the 28BYJ-48 on an ESP32 using MicroPython, alternating clockwise and counterclockwise revolutions.
//
// Buy this module: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver-manual
// More examples: https://github.com/shillehtek/examples
//

# 28BYJ-48 + ULN2003 - ESP32 MicroPython example
# IN1->GPIO 14, IN2->GPIO 27, IN3->GPIO 26, IN4->GPIO 25

from machine import Pin
import time

pins = [Pin(14, Pin.OUT), Pin(27, Pin.OUT), Pin(26, Pin.OUT), Pin(25, Pin.OUT)]

# Full-step sequence (faster, slightly less smooth than half-step)
FULL_STEP = [
    (1, 1, 0, 0),
    (0, 1, 1, 0),
    (0, 0, 1, 1),
    (1, 0, 0, 1),
]

def step(direction=1, steps=2048, delay_ms=3):
    seq = FULL_STEP if direction > 0 else tuple(reversed(FULL_STEP))
    for i in range(steps):
        pattern = seq[i % 4]
        for pin, val in zip(pins, pattern):
            pin.value(val)
        time.sleep_ms(delay_ms)

try:
    while True:
        print("CW one revolution")
        step(direction=1, steps=2048)  # 2048 = one revolution in full-step mode
        time.sleep(1)
        print("CCW one revolution")
        step(direction=-1, steps=2048)
        time.sleep(1)
except KeyboardInterrupt:
    for p in pins:
        p.value(0)
