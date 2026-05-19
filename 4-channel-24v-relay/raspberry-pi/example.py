# Raspberry Pi (RPi.GPIO) script using BCM pins 17, 27, 22, 23 to control four active-low relays in sequence and clean up on exit.
#
# Buy this module: https://shillehtek.com/products/4-channel-24v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-24v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 4-Channel 24V Relay Module - Raspberry Pi Example
# IN pins: GPIO 17, 27, 22, 23 (BCM)
# Active LOW logic.

import RPi.GPIO as GPIO
import time

PINS = [17, 27, 22, 23]

GPIO.setmode(GPIO.BCM)
for p in PINS:
    GPIO.setup(p, GPIO.OUT, initial=GPIO.HIGH)  # start OFF

try:
    while True:
        GPIO.output(17, GPIO.LOW)   # Relay 1 ON
        time.sleep(0.5)
        GPIO.output(17, GPIO.HIGH)  # Relay 1 OFF
        time.sleep(0.5)
        GPIO.output(27, GPIO.LOW)   # Relay 2 ON
        time.sleep(0.5)
        GPIO.output(27, GPIO.HIGH)  # Relay 2 OFF
        time.sleep(0.5)
        GPIO.output(22, GPIO.LOW)   # Relay 3 ON
        time.sleep(0.5)
        GPIO.output(22, GPIO.HIGH)  # Relay 3 OFF
        time.sleep(0.5)
        GPIO.output(23, GPIO.LOW)   # Relay 4 ON
        time.sleep(0.5)
        GPIO.output(23, GPIO.HIGH)  # Relay 4 OFF
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    for p in PINS:
        GPIO.output(p, GPIO.HIGH)  # ensure OFF
    GPIO.cleanup()
