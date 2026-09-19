# Use RPi.GPIO on a Raspberry Pi to detect both edges on GPIO17, increment a pulse counter via callback, and report vibration intensity once per second.
#
# Buy this module: https://shillehtek.com/products/vibration-sensor-sw-420-arduino-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vibration-sensor-sw-420-arduino-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# SW-420 Vibration Sensor - Raspberry Pi Example
# DO -> GPIO 17 (pin 11), VCC -> 3.3V (pin 1), GND -> GND (pin 6)

import RPi.GPIO as GPIO
import time

SENSOR_PIN = 17
pulse_count = 0

def on_vibration(channel):
    global pulse_count
    pulse_count += 1

GPIO.setmode(GPIO.BCM)
GPIO.setup(SENSOR_PIN, GPIO.IN)
# BOTH edges so idle-HIGH board revisions work too
GPIO.add_event_detect(SENSOR_PIN, GPIO.BOTH, callback=on_vibration)

print("Monitoring vibration (Ctrl+C to stop)...")

try:
    while True:
        pulse_count = 0
        time.sleep(1)

        if pulse_count == 0:
            print("Still")
        elif pulse_count < 20:
            print("Light vibration  ({} pulses)".format(pulse_count))
        else:
            print("STRONG vibration ({} pulses)".format(pulse_count))

except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.cleanup()
