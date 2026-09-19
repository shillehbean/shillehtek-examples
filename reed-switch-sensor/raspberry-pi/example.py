# Python script for Raspberry Pi that monitors a reed switch on BCM GPIO17 using an internal pull-up, debounces transitions, logs OPEN/CLOSED messages, and cleans up GPIO on exit.
#
# Buy this module: https://shillehtek.com/products/reed-switch-magnetic-sensor-normally-open-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/reed-switch-magnetic-sensor-normally-open-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# Reed Switch Door Monitor - Raspberry Pi Example
# Lead 1 -> GPIO 17 (pin 11), Lead 2 -> GND (pin 6)

import RPi.GPIO as GPIO
import time

REED_PIN = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(REED_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

last = GPIO.input(REED_PIN)
print("Monitoring door (Ctrl+C to stop)...")

try:
    while True:
        state = GPIO.input(REED_PIN)
        if state != last:
            time.sleep(0.03)          # debounce
            state = GPIO.input(REED_PIN)
            if state != last:
                if state == GPIO.LOW:
                    print("CLOSED - magnet present")
                else:
                    print("OPEN - magnet away!")
                last = state
        time.sleep(0.01)

except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.cleanup()
