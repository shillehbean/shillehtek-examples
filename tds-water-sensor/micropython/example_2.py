# MicroPython example for the Raspberry Pi Pico that reads the built-in ADC, converts to voltage, computes temperature-compensated TDS ppm, and prints a simple water-quality classification.
#
# Buy this module: https://shillehtek.com/products/tds-water-sensor-module-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tds-water-sensor-module-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Analog TDS Meter - Pico MicroPython Example
# A->GP26 (ADC0), +->3V3(OUT), -->GND

from machine import ADC
import time

adc = ADC(26)
WATER_TEMP = 25.0

def read_volts(n=30):
    total = 0
    for _ in range(n):
        total += adc.read_u16()
        time.sleep_ms(3)
    return total / n / 65535 * 3.3

def tds_ppm(volts, temp_c):
    v = volts / (1.0 + 0.02 * (temp_c - 25.0))
    return (133.42 * v**3 - 255.86 * v**2 + 857.39 * v) * 0.5

def quality(ppm):
    if ppm < 50:   return "RO / very pure"
    if ppm < 300:  return "good drinking water"
    if ppm < 600:  return "hard / mineral-rich"
    return "very high TDS"

print("TDS meter ready - dip the probe")
while True:
    volts = read_volts()
    ppm = tds_ppm(volts, WATER_TEMP)
    print("TDS: {:.0f} ppm ({})".format(ppm, quality(ppm)))
    time.sleep(1)
