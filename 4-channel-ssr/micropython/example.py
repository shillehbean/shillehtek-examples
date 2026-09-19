# MicroPython script that sets four GPIO outputs, turns them all on for 2 seconds, then turns them off one-by-one with a 0.5 second delay between each.
#
# Buy this module: https://shillehtek.com/products/4-channel-5v-ssr-module-arduino-esp32-raspberry
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-5v-ssr-module-arduino-esp32-raspberry-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

channels = [Pin(n, Pin.OUT, value=0) for n in (2, 3, 4, 5)]

while True:
    # all on together, then off one by one
    for ch in channels:
        ch.value(1)
    time.sleep(2)
    for ch in channels:
        ch.value(0)
        time.sleep(0.5)
