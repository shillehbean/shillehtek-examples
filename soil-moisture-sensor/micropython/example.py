# MicroPython script for a Raspberry Pi Pico that reads a 16-bit ADC on GP26, converts the calibrated reading into a moisture percentage, and prints the values every second.
#
# Buy this module: https://shillehtek.com/products/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit-manual
# More examples: https://github.com/shillehtek/examples
#

# Soil moisture on Raspberry Pi Pico (MicroPython)
# AO -> GP26 (ADC0)

from machine import ADC, Pin
import time

ao = ADC(26)

DRY = 52000   # 16-bit reading in air
WET = 22000   # 16-bit reading submerged

while True:
    raw = ao.read_u16()
    pct = (DRY - raw) * 100 // (DRY - WET)
    pct = max(0, min(100, pct))
    print("Raw={:5d}   Moisture={:3d} %".format(raw, pct))
    time.sleep(1)
