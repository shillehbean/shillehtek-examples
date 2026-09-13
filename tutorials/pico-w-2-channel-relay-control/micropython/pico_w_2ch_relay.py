# MicroPython script for Raspberry Pi Pico W that controls two relay outputs with active-low logic and cycles through several on/off combinations while ensuring a safe startup state.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-2-channel-relay-control
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

# Pico W pins:
# GP15 -> IN1
# GP14 -> IN2
RELAY1_GPIO = 15
RELAY2_GPIO = 14

relay1 = Pin(RELAY1_GPIO, Pin.OUT)
relay2 = Pin(RELAY2_GPIO, Pin.OUT)

# Many relay modules are ACTIVE LOW:
# 0 = ON, 1 = OFF
ACTIVE_LOW = True

def relay_on(relay: Pin):
    relay.value(0 if ACTIVE_LOW else 1)

def relay_off(relay: Pin):
    relay.value(1 if ACTIVE_LOW else 0)

# Safe startup: both OFF
relay_off(relay1)
relay_off(relay2)

while True:
    # Relay 1 ON, Relay 2 OFF
    relay_on(relay1)
    relay_off(relay2)
    time.sleep(1)

    # Relay 1 OFF, Relay 2 ON
    relay_off(relay1)
    relay_on(relay2)
    time.sleep(1)

    # Both ON
    relay_on(relay1)
    relay_on(relay2)
    time.sleep(1)

    # Both OFF
    relay_off(relay1)
    relay_off(relay2)
    time.sleep(1)
