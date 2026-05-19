# MicroPython example for RP2040 (Pico) that toggles the relay on GP15 (active LOW) every 2 seconds.
#
# Buy this module: https://shillehtek.com/products/1-channel-12v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-12v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

# 1-Channel 12V Relay Module - Pico MicroPython Example
# IN pin: GP15 (active LOW)
# VCC powered from external 12V supply, GND shared with Pico

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
