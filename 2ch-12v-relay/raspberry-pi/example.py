# Raspberry Pi Python script using RPi.GPIO to set BCM pins 17 and 27 HIGH to start OFF and then alternately toggle them LOW/HIGH to switch the relays, with clean shutdown on Ctrl‑C.
#
# Buy this module: https://shillehtek.com/products/2-channel-12v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-channel-12v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 2-Channel 12V Relay Module - Raspberry Pi Example
# IN pins: GPIO 17, 27 (BCM)
# Active LOW logic.

import RPi.GPIO as GPIO
import time

PINS = [17, 27]

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
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    for p in PINS:
        GPIO.output(p, GPIO.HIGH)  # ensure OFF
    GPIO.cleanup()
