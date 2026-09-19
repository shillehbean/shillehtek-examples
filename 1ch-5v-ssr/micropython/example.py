# MicroPython example that configures Pin 16 HIGH at start (SSR off) and then alternately pulls it LOW to turn the load on and HIGH to turn it off, with 4-second intervals.
#
# Buy this module: https://shillehtek.com/products/solid-state-relay-1ch-5v-active-low
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/solid-state-relay-1ch-5v-active-low-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

ch = Pin(16, Pin.OUT, value=1)   # start HIGH = OFF

def load_on():
    ch.value(0)     # active low

def load_off():
    ch.value(1)

while True:
    load_on()
    time.sleep(4)
    load_off()
    time.sleep(4)
