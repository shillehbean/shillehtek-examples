# MicroPython example for Raspberry Pi Pico: uses a local hx711.py driver to tare by averaging multiple readings, applies a scale factor, and computes/prints weight in grams periodically.
#
# Buy this module: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx711-weighing-pressure-sensor-module-large-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# HX711 Load Cell Amplifier - Pico MicroPython Example
# Library: hx711.py by endail (copy to your Pico as hx711.py)
# DT  -> GP14 (physical pin 19)
# SCK -> GP15 (physical pin 20)

from machine import Pin
from hx711 import hx711
import time

DT_PIN  = Pin(14, Pin.IN, pull=Pin.PULL_DOWN)
SCK_PIN = Pin(15, Pin.OUT)

scale = hx711(SCK_PIN, DT_PIN)
scale.set_gain(128)

# Tare: read current zero point
print("Taring...")
tare = 0
for _ in range(20):
    tare += scale.read()
    time.sleep_ms(50)
tare //= 20
print("Tare value:", tare)

# Replace with your calibrated scale factor
SCALE_FACTOR = 420.0

print("HX711 Load Cell Demo")
print("Place an item on the scale.")

while True:
    raw = scale.read()
    weight_g = (raw - tare) / SCALE_FACTOR
    print("Weight: {:.2f} g".format(weight_g))
    time.sleep_ms(500)
