# Uses a Raspberry Pi's BCM GPIO pins (17, 27, 22, 23) to sequentially pulse four relay inputs with 100 ms activation and 2 second spacing, and performs GPIO cleanup on exit.
#
# Buy this module: https://shillehtek.com/products/4-channel-relay-module-programmable-delay-6-24v
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-relay-module-programmable-delay-6-24v-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 4-channel programmable relay - sequence trigger from Pi GPIO

import RPi.GPIO as GPIO
import time

TRIGGERS = [17, 27, 22, 23]   # GPIO 17, 27, 22, 23
GPIO.setmode(GPIO.BCM)
for p in TRIGGERS:
    GPIO.setup(p, GPIO.OUT, initial=GPIO.LOW)

try:
    while True:
        for p in TRIGGERS:
            GPIO.output(p, GPIO.HIGH)
            time.sleep(0.1)
            GPIO.output(p, GPIO.LOW)
            time.sleep(2)
except KeyboardInterrupt:
    GPIO.cleanup()
