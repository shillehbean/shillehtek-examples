# MicroPython example for a Raspberry Pi Pico that sets 50 Hz PWM on GP15, converts angles to 0.5–2.5 ms pulses, and steps through positions.
#
# Buy this module: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy-manual
# More examples: https://github.com/shillehtek/examples
#

# MG995 on Raspberry Pi Pico (MicroPython)
# Signal -> GP15, V+ -> external 5-6V supply, GND common with Pico GND

from machine import Pin, PWM
import time

servo = PWM(Pin(15))
servo.freq(50)        # 50 Hz hobby servo

def angle(deg):
    # 0.5 ms = 0 deg, 2.5 ms = 180 deg, period = 20 ms
    pulse_us = 500 + (deg * 2000 // 180)
    duty = int(pulse_us * 65535 / 20000)
    servo.duty_u16(duty)

while True:
    for a in (0, 45, 90, 135, 180, 90):
        angle(a)
        time.sleep(0.5)
