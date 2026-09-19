# Monitors the KY-026 digital output on GPIO17 and logs state changes (flame detected / flame no longer detected) using RPi.GPIO.
#
# Buy this module: https://shillehtek.com/products/flame-sensor-ky-026-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/flame-sensor-ky-026-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# KY-026 Flame Sensor - Raspberry Pi Example
# D0 -> GPIO 17 (physical pin 11), + -> 3.3V (pin 1), G -> GND (pin 6)
# The Pi has no ADC, so we use the digital output only.

import RPi.GPIO as GPIO
import time

DO_PIN = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(DO_PIN, GPIO.IN)

try:
    print("Monitoring KY-026 flame sensor (Ctrl+C to stop)...")
    last_state = GPIO.input(DO_PIN)

    while True:
        state = GPIO.input(DO_PIN)

        # Only print when the state changes
        if state != last_state:
            if state == GPIO.HIGH:
                print("FLAME DETECTED!")
            else:
                print("Flame no longer detected.")
            last_state = state

        time.sleep(0.1)

except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.cleanup()
