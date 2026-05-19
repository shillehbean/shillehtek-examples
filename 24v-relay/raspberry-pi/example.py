# Raspberry Pi Python script using RPi.GPIO that initializes GPIO23 high (relay off), toggles the relay every 2 seconds, and performs cleanup on KeyboardInterrupt.
#
# Buy this module: https://shillehtek.com/products/1-channel-24v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-24v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 1-Channel 24V Relay Module - Raspberry Pi Example
# IN pin: GPIO 23 (active LOW)
# VCC powered from external 24V supply, GND shared with Pi

import RPi.GPIO as GPIO
import time

RELAY_PIN = 23

GPIO.setmode(GPIO.BCM)
GPIO.setup(RELAY_PIN, GPIO.OUT, initial=GPIO.HIGH)  # start OFF

try:
    while True:
        print("Relay ON")
        GPIO.output(RELAY_PIN, GPIO.LOW)   # active LOW
        time.sleep(2)

        print("Relay OFF")
        GPIO.output(RELAY_PIN, GPIO.HIGH)
        time.sleep(2)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.output(RELAY_PIN, GPIO.HIGH)
    GPIO.cleanup()
