# MicroPython example for a Pico that sets GP2 and GP3 as outputs initialized HIGH (relays OFF) and alternately drives them LOW/HIGH to switch the relays, handling KeyboardInterrupt to stop.
#
# Buy this module: https://shillehtek.com/products/2-channel-12v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-channel-12v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

# 2-Channel 12V Relay Module - Pico MicroPython Example
# IN pins: GP2, GP3
# Active LOW logic.

from machine import Pin
from time import sleep

relay1 = Pin(2, Pin.OUT, value=1)  # start OFF (HIGH)
relay2 = Pin(3, Pin.OUT, value=1)  # start OFF (HIGH)

try:
    while True:
        relay1.value(0)  # Relay 1 ON
        sleep(0.5)
        relay1.value(1)  # Relay 1 OFF
        sleep(0.5)
        relay2.value(0)  # Relay 2 ON
        sleep(0.5)
        relay2.value(1)  # Relay 2 OFF
        sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
