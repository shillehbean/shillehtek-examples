# Uses RPi.GPIO to pulse GPIO17 HIGH for 150 ms to trigger the relay in a loop every 30 seconds, with cleanup on KeyboardInterrupt.
#
# Buy this module: https://shillehtek.com/products/ac-220v-1-channel-time-delay-relay-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-220v-1-channel-time-delay-relay-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 1-channel programmable delay relay - fire trigger from Raspberry Pi

import RPi.GPIO as GPIO
import time

TRIG = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG, GPIO.OUT, initial=GPIO.LOW)

try:
    while True:
        GPIO.output(TRIG, GPIO.HIGH)
        time.sleep(0.15)
        GPIO.output(TRIG, GPIO.LOW)
        time.sleep(30)
except KeyboardInterrupt:
    GPIO.cleanup()
