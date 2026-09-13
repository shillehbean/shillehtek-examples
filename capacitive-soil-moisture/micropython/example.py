# Reads the sensor on a Pico ADC pin with read_u16(), clamps and scales the calibrated 16-bit reading to a 0–100% moisture value, and prints the raw and percent readings once per second.
#
# Buy this module: https://shillehtek.com/products/Analog
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/capacitive-soil-moisture-sensor-v1-2-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Capacitive Soil Moisture Sensor V1.2 - Pico (MicroPython)
# AOUT -> GP26 (ADC0), VCC -> 3V3, GND -> GND

from machine import ADC, Pin
import time

soil = ADC(Pin(26))

# 16-bit value on Pico (read_u16). Calibrate:
DRY_VALUE = 50000
WET_VALUE = 22000

while True:
    raw = soil.read_u16()
    clamped = max(WET_VALUE, min(DRY_VALUE, raw))
    percent = int((DRY_VALUE - clamped) * 100 / (DRY_VALUE - WET_VALUE))
    print("Raw:", raw, " Moisture:", percent, "%")
    time.sleep(1)
