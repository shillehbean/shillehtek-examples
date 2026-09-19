# Drives a TT gear motor from a Raspberry Pi Pico using MicroPython by toggling direction pins and setting PWM duty for soft-start, cruise, stop, and reverse.
#
# Buy this module: https://shillehtek.com/products/tt-gear-motor-3-6v-1-48-125rpm
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tt-gear-motor-3-6v-1-48-125rpm-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TT motor on L298N from a Pico:
# IN1=GP2, IN2=GP3, ENA=GP4 (PWM). Grounds shared.

from machine import Pin, PWM
import time

in1 = Pin(2, Pin.OUT)
in2 = Pin(3, Pin.OUT)
ena = PWM(Pin(4))
ena.freq(1000)

def drive(percent):
    """-100..100; negative = reverse."""
    if percent >= 0:
        in1.value(1); in2.value(0)
    else:
        in1.value(0); in2.value(1)
        percent = -percent
    ena.duty_u16(int(65535 * percent / 100))

# Soft start forward, cruise, stop, reverse
for p in range(0, 81, 10):
    drive(p)
    time.sleep(0.1)
time.sleep(2)
drive(0)
time.sleep(0.5)
drive(-60)
time.sleep(2)
drive(0)
