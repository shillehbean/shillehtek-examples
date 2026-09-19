# Runs on MicroPython (e.g., RP2040), reads ADC0 (GP26) samples to calculate RMS voltage from the AC signal over a time window and prints the measured AC voltage.
#
# Buy this module: https://shillehtek.com/products/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import ADC
import math
import time

adc = ADC(26)                # GP26 / ADC0
CAL = 250.0                  # tune against a multimeter

def read_rms(window_ms=200):
    n = 0
    total = 0
    total_sq = 0
    t_end = time.ticks_add(time.ticks_ms(), window_ms)
    while time.ticks_diff(t_end, time.ticks_ms()) > 0:
        raw = adc.read_u16()
        total += raw
        total_sq += raw * raw
        n += 1
    mean = total / n
    var = total_sq / n - mean * mean
    rms = math.sqrt(var if var > 0 else 0)
    return rms * (3.3 / 65535) * CAL

while True:
    print("AC voltage: {:.1f} V".format(read_rms()))
    time.sleep(1)
