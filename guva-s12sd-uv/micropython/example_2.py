# MicroPython example for the Raspberry Pi Pico: reads ADC0 (GP26) with read_u16(), averages samples, converts to millivolts using the Pico's 3.3V scale, estimates UV index as mV/100, and prints the readings.
#
# Buy this module: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/uv-sensor-guva-s12sd-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# GUVA-S12SD UV Sensor - Pico MicroPython Example
# SIG Pin: GP26 (ADC0, physical pin 31), VCC: 3V3(OUT), GND: GND
# UV Index is approximately the output voltage in mV divided by 100

from machine import ADC
import time

adc = ADC(26)             # GP26 = ADC0
CONVERSION = 3.3 / 65535  # read_u16() returns 0-65535 across 0-3.3V

while True:
    # Average several readings to smooth out ADC noise
    total = 0
    for _ in range(16):
        total += adc.read_u16()
        time.sleep_ms(2)
    millivolts = (total / 16) * CONVERSION * 1000

    # Approximate solar UV Index: mV / 100
    uv_index = millivolts / 100

    print("Voltage: {:.0f} mV | UV Index: {:.1f}".format(millivolts, uv_index))
    time.sleep(1)
