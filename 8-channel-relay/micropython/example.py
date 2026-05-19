# Sets up eight Raspberry Pi Pico GPIOs as outputs (active-LOW) in MicroPython and repeatedly activates each relay in turn with 0.5s pauses.
#
# Buy this module: https://shillehtek.com/products/8-channel-5v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/8-channel-5v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

# 8-Channel 5V Relay Module - Pico MicroPython Example
# IN pins: GP2, GP3, GP4, GP5, GP6, GP7, GP8, GP9
# Active LOW logic.

from machine import Pin
from time import sleep

relay1 = Pin(2, Pin.OUT, value=1)  # start OFF (HIGH)
relay2 = Pin(3, Pin.OUT, value=1)  # start OFF (HIGH)
relay3 = Pin(4, Pin.OUT, value=1)  # start OFF (HIGH)
relay4 = Pin(5, Pin.OUT, value=1)  # start OFF (HIGH)
relay5 = Pin(6, Pin.OUT, value=1)  # start OFF (HIGH)
relay6 = Pin(7, Pin.OUT, value=1)  # start OFF (HIGH)
relay7 = Pin(8, Pin.OUT, value=1)  # start OFF (HIGH)
relay8 = Pin(9, Pin.OUT, value=1)  # start OFF (HIGH)

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
        relay5.value(0)  # Relay 5 ON
        sleep(0.5)
        relay5.value(1)  # Relay 5 OFF
        sleep(0.5)
        relay6.value(0)  # Relay 6 ON
        sleep(0.5)
        relay6.value(1)  # Relay 6 OFF
        sleep(0.5)
        relay7.value(0)  # Relay 7 ON
        sleep(0.5)
        relay7.value(1)  # Relay 7 OFF
        sleep(0.5)
        relay8.value(0)  # Relay 8 ON
        sleep(0.5)
        relay8.value(1)  # Relay 8 OFF
        sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
