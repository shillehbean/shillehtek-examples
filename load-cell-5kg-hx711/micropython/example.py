# MicroPython example for RP2040 (Pico) that bit-bangs the HX711 on GP14/GP15 to tare, read averaged raw counts, convert to grams using a calibration factor, and print results.
#
# Buy this module: https://shillehtek.com/products/load-cell-5kg-hx711-arduino-esp32-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-5kg-hx711-arduino-esp32-kit-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 5kg Load Cell + HX711 - Pico MicroPython Example (no library needed)
# DT -> GP14, SCK -> GP15, VCC -> 3V3(OUT), GND -> GND

from machine import Pin
import time

dt = Pin(14, Pin.IN)
sck = Pin(15, Pin.OUT, value=0)

CALIBRATION_FACTOR = 1.0   # (raw_with_weight - raw_empty) / grams

def read_raw():
    while dt.value() == 1:          # wait for data ready
        time.sleep_ms(1)

    value = 0
    for _ in range(24):             # clock out 24 data bits
        sck.value(1)
        sck.value(0)
        value = (value << 1) | dt.value()

    sck.value(1)                    # 25th pulse = channel A, gain 128
    sck.value(0)

    if value & 0x800000:            # sign-extend
        value -= 1 << 24
    return value

def read_average(n=10):
    return sum(read_raw() for _ in range(n)) / n

print("Remove all weight... taring")
time.sleep(2)
zero = read_average(20)
print("Tared. Raw zero =", int(zero))

while True:
    raw = read_average(10)
    grams = (raw - zero) / CALIBRATION_FACTOR
    print("Raw: {:8.0f}  |  Weight: {:8.1f} g".format(raw - zero, grams))
    time.sleep(0.5)
