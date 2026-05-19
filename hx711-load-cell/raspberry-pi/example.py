# Python script for Raspberry Pi using the hx711 pip package: configures GPIO pins, zeros the scale, sets a scale ratio, and prints averaged weight readings in grams in a loop until interrupted.
#
# Buy this module: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx711-weighing-pressure-sensor-module-large-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# HX711 Load Cell Amplifier - Raspberry Pi Example
# Install: pip3 install hx711
# DT  -> GPIO 5  (physical pin 29)
# SCK -> GPIO 6  (physical pin 31)

import RPi.GPIO as GPIO
import time
from hx711 import HX711

GPIO.setmode(GPIO.BCM)

DT_PIN  = 5
SCK_PIN = 6

hx = HX711(dout_pin=DT_PIN, pd_sck_pin=SCK_PIN)

# Reset and tare
hx.reset()
hx.zero(readings=30)

# Replace with your calibrated scale factor (raw_value / known_weight_in_grams)
SCALE_FACTOR = 102.372
hx.set_scale_ratio(SCALE_FACTOR)

print("HX711 Load Cell Demo")
print("Place an item on the scale. Press Ctrl+C to quit.")

try:
    while True:
        weight = hx.get_weight_mean(readings=10)
        print("Weight: {:.2f} g".format(weight))
        time.sleep(0.5)
except (KeyboardInterrupt, SystemExit):
    print("\nStopped by user")
finally:
    GPIO.cleanup()
