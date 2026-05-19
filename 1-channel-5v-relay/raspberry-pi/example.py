# Raspberry Pi Python script using RPi.GPIO to toggle GPIO23 (active LOW) every 2 seconds and perform GPIO cleanup on exit.
#
# Buy this module: https://shillehtek.com/products/1-channel-5v-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-channel-5v-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 1-Channel 5V Relay Module - Raspberry Pi Example
# IN pin: GPIO 23 (active LOW)

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
