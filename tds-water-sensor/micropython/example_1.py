# MicroPython example for ESP32 that reads the ADC (GPIO34) averaged in microvolts, applies temperature compensation, computes TDS ppm, and prints values repeatedly.
#
# Buy this module: https://shillehtek.com/products/tds-water-sensor-module-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tds-water-sensor-module-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Analog TDS Meter - ESP32 MicroPython Example
# A->GPIO 34, +->3V3, -->GND

from machine import ADC, Pin
import time

adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)

WATER_TEMP = 25.0

def read_volts(n=30):
    total = 0
    for _ in range(n):
        total += adc.read_uv()
        time.sleep_ms(3)
    return total / n / 1_000_000

def tds_ppm(volts, temp_c):
    v = volts / (1.0 + 0.02 * (temp_c - 25.0))
    return (133.42 * v**3 - 255.86 * v**2 + 857.39 * v) * 0.5

print("TDS meter ready - dip the probe")
while True:
    volts = read_volts()
    print("V: {:.3f} | TDS: {:.0f} ppm".format(volts, tds_ppm(volts, WATER_TEMP)))
    time.sleep(1)
