# MicroPython example converting angles to PWM pulse widths using machine.PWM to drive pan and tilt servos and run a continuous lazy-eight patrol.
#
# Buy this module: https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pan-tilt-servo-bracket-kit-sg90-mg90s-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
import time

pan = PWM(Pin(14));  pan.freq(50)
tilt = PWM(Pin(15)); tilt.freq(50)

def angle(pwm, deg):
    deg = max(0, min(180, deg))          # clamp
    us = 500 + deg * (2000 / 180)        # 500-2500 us
    pwm.duty_u16(int(us * 65535 / 20000))

angle(pan, 90); angle(tilt, 90)
time.sleep(1)

while True:
    # lazy-eight patrol
    for d in range(30, 151, 2):
        angle(pan, d)
        angle(tilt, 90 + (25 if d < 90 else -25))
        time.sleep(0.02)
    for d in range(150, 29, -2):
        angle(pan, d)
        angle(tilt, 90 + (-25 if d < 90 else 25))
        time.sleep(0.02)
