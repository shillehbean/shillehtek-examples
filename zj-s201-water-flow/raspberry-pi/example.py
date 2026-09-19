# Raspberry Pi Python example using RPi.GPIO event detection on GPIO17 to count pulses and report flow rate and accumulated liters once per second, with cleanup on KeyboardInterrupt.
#
# Buy this module: https://shillehtek.com/products/water-flow-sensor-g1-2-1-30l-min
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/water-flow-sensor-g1-2-1-30l-min-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# ZJ-S201 Water Flow Sensor - Raspberry Pi Example
# Yellow->GPIO17, Red->5V, Black->GND

import RPi.GPIO as GPIO
import time

FLOW_PIN = 17
PULSES_PER_LMIN = 7.5

pulses = 0
def on_pulse(channel):
    global pulses
    pulses += 1

GPIO.setmode(GPIO.BCM)
GPIO.setup(FLOW_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(FLOW_PIN, GPIO.FALLING, callback=on_pulse)

total_liters = 0.0
print("Flow meter ready - open the tap!")
try:
    while True:
        pulses = 0
        time.sleep(1)
        lmin = pulses / PULSES_PER_LMIN
        total_liters += lmin / 60
        print(f"Flow: {lmin:.2f} L/min | Total: {total_liters:.3f} L")
except KeyboardInterrupt:
    GPIO.cleanup()
    print("Stopped by user")
