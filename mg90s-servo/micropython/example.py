# Runs on a Pico with MicroPython to drive the MG90S via PWM on GP15, mapping angles to duty_u16 values for a 0–180° sweep.
#
# Buy this module: https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane-manual
# More examples: https://github.com/shillehtek/examples
#

# MG90S Servo - Pico MicroPython Example
# Signal pin: GP15
# Power the servo from a separate 5V supply, share ground with Pico.

from machine import Pin, PWM
from time import sleep

servo = PWM(Pin(15))
servo.freq(50)  # 50 Hz for hobby servos

# 16-bit duty mapping for 500 - 2400 us pulse on a 20000 us period
MIN_DUTY = 1638   # ~500 us  -> 0 degrees
MAX_DUTY = 7864   # ~2400 us -> 180 degrees

def write_angle(angle):
    if angle < 0:
        angle = 0
    if angle > 180:
        angle = 180
    duty = MIN_DUTY + int((MAX_DUTY - MIN_DUTY) * angle / 180)
    servo.duty_u16(duty)

try:
    while True:
        for a in range(0, 181, 2):
            write_angle(a)
            sleep(0.015)
        for a in range(180, -1, -2):
            write_angle(a)
            sleep(0.015)
except KeyboardInterrupt:
    print("Stopped by user")
    servo.deinit()
