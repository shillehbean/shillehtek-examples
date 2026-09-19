# Raspberry Pi Python script using RPi.GPIO to read the SW-520D on GPIO17 with debounce, printing tilt/level messages and cleaning up on exit.
#
# Buy this module: https://shillehtek.com/products/tilt-switch-sw-520d-vibration-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tilt-switch-sw-520d-vibration-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# SW-520D Tilt Switch Module - Raspberry Pi Example
# D0->GPIO17 (pin 11), VCC->3.3V, GND->GND

import RPi.GPIO as GPIO
import time

TILT_PIN = 17
DEBOUNCE_S = 0.06

GPIO.setmode(GPIO.BCM)
GPIO.setup(TILT_PIN, GPIO.IN)

stable = GPIO.input(TILT_PIN)
last_reading = stable
last_change = time.time()

print("Tilt sensor ready - tip me over!")
try:
    while True:
        reading = GPIO.input(TILT_PIN)

        if reading != last_reading:
            last_change = time.time()
            last_reading = reading

        if time.time() - last_change > DEBOUNCE_S and reading != stable:
            stable = reading
            print("TILTED!" if stable else "Level again")

        time.sleep(0.005)
except KeyboardInterrupt:
    GPIO.cleanup()
    print("Stopped by user")
