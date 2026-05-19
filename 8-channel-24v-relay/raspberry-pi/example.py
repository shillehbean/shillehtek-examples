# Raspberry Pi Python script using RPi.GPIO to cycle relays wired to BCM pins 17, 27, 22, 23, 24, 25, 5, and 6 (active LOW).
#
# Buy this module: https://shillehtek.com/products/8-channel-12v-relay-module-copy
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/8-channel-12v-relay-module-copy-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 8-Channel 24V Relay Module - Raspberry Pi Example
# IN pins: GPIO 17, 27, 22, 23, 24, 25, 5, 6 (BCM)
# Active LOW logic.

import RPi.GPIO as GPIO
import time

PINS = [17, 27, 22, 23, 24, 25, 5, 6]

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
        GPIO.output(24, GPIO.LOW)   # Relay 5 ON
        time.sleep(0.5)
        GPIO.output(24, GPIO.HIGH)  # Relay 5 OFF
        time.sleep(0.5)
        GPIO.output(25, GPIO.LOW)   # Relay 6 ON
        time.sleep(0.5)
        GPIO.output(25, GPIO.HIGH)  # Relay 6 OFF
        time.sleep(0.5)
        GPIO.output(5, GPIO.LOW)   # Relay 7 ON
        time.sleep(0.5)
        GPIO.output(5, GPIO.HIGH)  # Relay 7 OFF
        time.sleep(0.5)
        GPIO.output(6, GPIO.LOW)   # Relay 8 ON
        time.sleep(0.5)
        GPIO.output(6, GPIO.HIGH)  # Relay 8 OFF
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    for p in PINS:
        GPIO.output(p, GPIO.HIGH)  # ensure OFF
    GPIO.cleanup()
