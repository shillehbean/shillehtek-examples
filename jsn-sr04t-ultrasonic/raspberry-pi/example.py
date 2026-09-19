# Raspberry Pi Python example using RPi.GPIO to pulse the JSN-SR04T trigger, time the echo pulse to compute distance (using a median of readings), print distance or warnings, and clean up GPIO on exit.
#
# Buy this module: https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# JSN-SR04T - Raspberry Pi Example
# Trig->GPIO23, Echo->GPIO24 (via 1k/2k divider)

import RPi.GPIO as GPIO
import time, statistics

TRIG, ECHO = 23, 24
GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG, GPIO.OUT, initial=0)
GPIO.setup(ECHO, GPIO.IN)

def read_once_cm():
    GPIO.output(TRIG, 1); time.sleep(0.00001)
    GPIO.output(TRIG, 0)
    t0 = time.time()
    while GPIO.input(ECHO) == 0:
        if time.time() - t0 > 0.04: return -1
    start = time.time()
    while GPIO.input(ECHO) == 1:
        if time.time() - start > 0.04: return -1
    return (time.time() - start) * 17150

try:
    print("JSN-SR04T ready (blind zone < ~25 cm)")
    while True:
        vals = []
        for _ in range(3):
            d = read_once_cm()
            if d > 0: vals.append(d)
            time.sleep(0.06)
        if not vals:
            print("Out of range / no echo")
        else:
            cm = statistics.median(vals)
            if cm < 25: print("Too close (blind zone)")
            else:       print(f"Distance: {cm:.1f} cm")
        time.sleep(0.3)
except KeyboardInterrupt:
    GPIO.cleanup()
    print("Stopped by user")
