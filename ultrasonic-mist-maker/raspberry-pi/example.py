# Uses a Raspberry Pi GPIO (BCM17) to switch a 5V relay (often active-LOW) turning the mist maker on for 5 seconds and off for 55 seconds in a loop, with cleanup on Ctrl+C.
#
# Buy this module: https://shillehtek.com/products/dc-5v-ultrasonic-mist-maker-humidifier-module-108khz-usb
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dc-5v-ultrasonic-mist-maker-humidifier-module-108khz-usb-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Toggle the mist maker through a 5V relay on GPIO 17 (Pi)
# Many relay modules are active-LOW: LOW = ON, HIGH = OFF

import RPi.GPIO as GPIO
import time

RELAY = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(RELAY, GPIO.OUT, initial=GPIO.HIGH)   # start OFF

try:
    while True:
        GPIO.output(RELAY, GPIO.LOW)   # mist ON
        time.sleep(5)
        GPIO.output(RELAY, GPIO.HIGH)  # mist OFF
        time.sleep(55)
except KeyboardInterrupt:
    GPIO.cleanup()
