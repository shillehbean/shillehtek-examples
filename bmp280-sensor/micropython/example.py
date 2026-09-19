# Runs on MicroPython (e.g. Raspberry Pi Pico) to read temperature and pressure from a BMP280 over I2C and print the results to the REPL.
#
# Buy this module: https://shillehtek.com/products/shillehtek-bmp280-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bmp280-i2c-iic-digital-atmospheric-pressure-temperature-altitude-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BMP280 - Pico MicroPython Example
# Requires bmp280.py from David Stenwall's micropython-bmp280 library.

from machine import Pin, I2C
from bmp280 import BMP280
import time

i2c = I2C(0, scl=Pin(5), sda=Pin(4), freq=400_000)
bmp = BMP280(i2c, addr=0x76)

while True:
    print("Temp:     {:.2f} C".format(bmp.temperature))
    print("Pressure: {:.2f} hPa".format(bmp.pressure / 100))
    print()
    time.sleep(1)
