# Configures a PWM output in MicroPython (duty_u16 resolution) and runs a sequence that slowly ramps the duty, flashes the output, then turns it off to demonstrate PWM control on boards like the RP2040 or other MicroPython-compatible targets.
#
# Buy this module: https://shillehtek.com/products/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/irf520-mosfet-driver-module-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
import time

sig = PWM(Pin(15))
sig.freq(1000)

def set_duty(pct):
    sig.duty_u16(int(pct * 65535))

while True:
    # slow ramp up, fast blink, off
    for p in range(0, 101, 2):
        set_duty(p / 100)
        time.sleep(0.05)
    for _ in range(4):
        set_duty(0); time.sleep(0.2)
        set_duty(1); time.sleep(0.2)
    set_duty(0)
    time.sleep(1)
