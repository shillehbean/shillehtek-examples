# Control the SG92R from a Raspberry Pi Pico running MicroPython by outputting 50 Hz PWM on GP15 and mapping 0–180° to 0.5–2.5 ms pulse widths using duty_u16.
#
# Buy this module: https://shillehtek.com/products/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sg92r-micro-servo-motor-9g-carbon-fiber-gears-2-5kg-for-rc-plane-manual
# More examples: https://github.com/shillehtek/examples
#

# SG92R Servo - Pico MicroPython
# PWM on GP15 at 50 Hz; duty 1638 = 0.5 ms (0 deg), 8191 = 2.5 ms (180 deg)

from machine import Pin, PWM
import time

servo = PWM(Pin(15))
servo.freq(50)

def set_angle(angle):
    # Map 0-180 to 1638-8191 (16-bit duty for 0.5-2.5ms pulse at 50 Hz)
    duty = int(1638 + (angle / 180) * (8191 - 1638))
    servo.duty_u16(duty)

while True:
    for a in range(0, 181, 5):
        set_angle(a)
        time.sleep(0.02)
    for a in range(180, -1, -5):
        set_angle(a)
        time.sleep(0.02)
