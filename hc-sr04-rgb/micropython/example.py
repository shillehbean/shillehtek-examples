# MicroPython script that uses time_pulse_us and the NeoPixel driver to read distance from the HC‑SR04 and set the onboard RGB LEDs according to the measured range.
#
# Buy this module: https://shillehtek.com/products/shillehtek-hc-sr04-with-rgb-light-distance
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-hc-sr04-with-rgb-light-distance-manual
# More examples: https://github.com/shillehtek/examples
#

# Uses a ready-made NeoPixel driver (e.g. 'neopixel' module on MicroPython).
# Wiring: Trig=GP2, Echo=GP3 (via divider), RGB_IN=GP6 (via shifter).

from machine import Pin, time_pulse_us
import time, neopixel

TRIG = Pin(2, Pin.OUT)
ECHO = Pin(3, Pin.IN)

NUM_LEDS = 4
np = neopixel.NeoPixel(Pin(6), NUM_LEDS)

def ping_cm():
    TRIG.value(0); time.sleep_us(2)
    TRIG.value(1); time.sleep_us(10); TRIG.value(0)
    us = time_pulse_us(ECHO, 1, 30_000)
    return -1 if us <= 0 else (us / 58.0)

def set_all(r, g, b):
    for i in range(NUM_LEDS):
        np[i] = (r, g, b)
    np.write()

while True:
    cm = ping_cm()
    print("Distance:", cm, "cm")
    if cm < 0:        set_all(0, 0, 30)
    elif cm < 15:     set_all(60, 0, 0)
    elif cm < 50:     set_all(60, 30, 0)
    else:             set_all(0, 40, 0)
    time.sleep(0.08)
