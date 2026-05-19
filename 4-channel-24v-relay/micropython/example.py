# MicroPython example for a Pico that sets GP2–GP5 as outputs (active-high idle) and toggles each active-low relay on and off with 0.5 s delays.
#
# Buy this module: https://shillehtek.com/products/4-channel-24v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-24v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

# 4-Channel 24V Relay Module - Pico MicroPython Example
# IN pins: GP2, GP3, GP4, GP5
# Active LOW logic.

from machine import Pin
from time import sleep

relay1 = Pin(2, Pin.OUT, value=1)  # start OFF (HIGH)
relay2 = Pin(3, Pin.OUT, value=1)  # start OFF (HIGH)
relay3 = Pin(4, Pin.OUT, value=1)  # start OFF (HIGH)
relay4 = Pin(5, Pin.OUT, value=1)  # start OFF (HIGH)

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
        relay3.value(0)  # Relay 3 ON
        sleep(0.5)
        relay3.value(1)  # Relay 3 OFF
        sleep(0.5)
        relay4.value(0)  # Relay 4 ON
        sleep(0.5)
        relay4.value(1)  # Relay 4 OFF
        sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
