# Raspberry Pi Python script that bit-bangs the HX711 via RPi.GPIO to read raw 24-bit values, tare the sensor, and compute averaged weight in grams (prints continuously).
#
# Buy this module: https://shillehtek.com/products/load-cell-5kg-hx711-arduino-esp32-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-5kg-hx711-arduino-esp32-kit-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 5kg Load Cell + HX711 - Raspberry Pi Example (no library needed)
# DT -> GPIO 5 (pin 29), SCK -> GPIO 6 (pin 31), VCC -> 3.3V (pin 1)

import time
import RPi.GPIO as GPIO

DT, SCK = 5, 6
CALIBRATION_FACTOR = 1.0   # (raw_with_weight - raw_empty) / grams

GPIO.setmode(GPIO.BCM)
GPIO.setup(DT, GPIO.IN)
GPIO.setup(SCK, GPIO.OUT, initial=GPIO.LOW)

def read_raw():
    # Wait until the HX711 signals data ready (DT goes low)
    while GPIO.input(DT) == 1:
        time.sleep(0.001)

    value = 0
    for _ in range(24):                 # clock out 24 data bits
        GPIO.output(SCK, GPIO.HIGH)
        GPIO.output(SCK, GPIO.LOW)
        value = (value << 1) | GPIO.input(DT)

    GPIO.output(SCK, GPIO.HIGH)         # 25th pulse = channel A, gain 128
    GPIO.output(SCK, GPIO.LOW)

    if value & 0x800000:                # sign-extend the 24-bit result
        value -= 1 << 24
    return value

def read_average(n=10):
    return sum(read_raw() for _ in range(n)) / n

print("Remove all weight... taring")
time.sleep(2)
zero = read_average(20)
print("Tared. Raw zero = {:.0f}".format(zero))

try:
    while True:
        raw = read_average(10)
        grams = (raw - zero) / CALIBRATION_FACTOR
        print("Raw: {:8.0f}  |  Weight: {:8.1f} g".format(raw - zero, grams))
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.cleanup()
