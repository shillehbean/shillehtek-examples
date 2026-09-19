# Raspberry Pi Python (bit-banged) example that reads 24-bit samples from the HX711 on GPIO, tares the sensor, and continuously prints averaged weight in kilograms after applying a calibration factor.
#
# Buy this module: https://shillehtek.com/products/load-cell-50kg-half-bridge-strain-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/load-cell-50kg-half-bridge-strain-sensor-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 4x 50kg Load Cells + HX711 - Raspberry Pi Example (no library needed)
# DT -> GPIO 5 (pin 29), SCK -> GPIO 6 (pin 31), VCC -> 3.3V (pin 1)

import time
import RPi.GPIO as GPIO

DT, SCK = 5, 6
CALIBRATION_FACTOR = 1.0   # tared raw / known kg

GPIO.setmode(GPIO.BCM)
GPIO.setup(DT, GPIO.IN)
GPIO.setup(SCK, GPIO.OUT, initial=GPIO.LOW)

def read_raw():
    while GPIO.input(DT) == 1:      # wait for data ready
        time.sleep(0.001)
    value = 0
    for _ in range(24):             # 24 data bits
        GPIO.output(SCK, GPIO.HIGH)
        GPIO.output(SCK, GPIO.LOW)
        value = (value << 1) | GPIO.input(DT)
    GPIO.output(SCK, GPIO.HIGH)     # gain 128, channel A
    GPIO.output(SCK, GPIO.LOW)
    if value & 0x800000:
        value -= 1 << 24
    return value

def read_average(n=10):
    return sum(read_raw() for _ in range(n)) / n

print("Empty the platform... taring")
time.sleep(2)
zero = read_average(20)
print("Ready - step on!")

try:
    while True:
        kg = (read_average(10) - zero) / CALIBRATION_FACTOR
        print("Weight: {:.2f} kg".format(kg))
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.cleanup()
