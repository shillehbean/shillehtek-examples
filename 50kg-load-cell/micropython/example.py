# MicroPython (RP2040/Pico) bit-banged example that reads raw 24-bit values from the HX711, performs a tare, applies a calibration factor, and prints averaged weight (kg) periodically.
#
# Buy this module: https://shillehtek.com/products/load-cell-50kg-half-bridge-strain-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-50kg-half-bridge-strain-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 4x 50kg Load Cells + HX711 - Pico MicroPython Example (no library)
# DT -> GP14, SCK -> GP15, VCC -> 3V3(OUT)

from machine import Pin
import time

dt = Pin(14, Pin.IN)
sck = Pin(15, Pin.OUT, value=0)

CALIBRATION_FACTOR = 1.0   # tared raw / known kg

def read_raw():
    while dt.value() == 1:
        time.sleep_ms(1)
    value = 0
    for _ in range(24):
        sck.value(1)
        sck.value(0)
        value = (value << 1) | dt.value()
    sck.value(1)               # gain 128, channel A
    sck.value(0)
    if value & 0x800000:
        value -= 1 << 24
    return value

def read_average(n=10):
    return sum(read_raw() for _ in range(n)) / n

print("Empty the platform... taring")
time.sleep(2)
zero = read_average(20)
print("Ready - step on!")

while True:
    kg = (read_average(10) - zero) / CALIBRATION_FACTOR
    print("Weight: {:.2f} kg".format(kg))
    time.sleep(0.5)
