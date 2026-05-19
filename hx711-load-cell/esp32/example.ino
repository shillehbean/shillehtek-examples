// MicroPython example for ESP32: uses an HX711 driver to tare by averaging readings, sets gain, and repeatedly reads raw values to calculate and print weight in grams using a scale factor.
//
// Buy this module: https://shillehtek.com/products/hx711-weighing-pressure-sensor-module-large-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx711-weighing-pressure-sensor-module-large-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

# HX711 Load Cell Amplifier - ESP32 MicroPython Example
# Library: hx711.py by SergeyPiskunov (copy to your ESP32 as hx711.py)
# DT  -> GPIO 4
# SCK -> GPIO 5

from machine import Pin
from hx711 import HX711
import time

DT_PIN  = Pin(4, Pin.IN, pull=Pin.PULL_DOWN)
SCK_PIN = Pin(5, Pin.OUT)

hx = HX711(d_out=4, pd_sck=5)
hx.set_gain(128)

# Tare
print("Taring...")
tare = 0
for _ in range(20):
    tare += hx.read()
    time.sleep_ms(50)
tare //= 20
print("Tare value:", tare)

SCALE_FACTOR = 420.0

print("HX711 Load Cell Demo")
print("Place an item on the scale.")

while True:
    raw = hx.read()
    weight_g = (raw - tare) / SCALE_FACTOR
    print("Weight: {:.2f} g".format(weight_g))
    time.sleep_ms(500)
