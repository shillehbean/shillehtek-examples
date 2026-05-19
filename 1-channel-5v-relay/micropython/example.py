# MicroPython example for a Pico that initializes GP15 HIGH (relay off) and toggles the relay (active LOW) every 2 seconds.
#
# Buy this module: https://shillehtek.com/products/1-channel-5v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-5v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

# 1-Channel 5V Relay Module - Pico MicroPython Example
# IN pin: GP15 (active LOW)

from machine import Pin
import time

relay = Pin(15, Pin.OUT, value=1)  # start HIGH (relay OFF)

while True:
    print("Relay ON")
    relay.value(0)   # active LOW
    time.sleep(2)

    print("Relay OFF")
    relay.value(1)
    time.sleep(2)
