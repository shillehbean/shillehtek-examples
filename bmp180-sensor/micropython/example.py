# Runs on a MicroPython board (example: Pico) to read temperature, pressure, and altitude from a BMP180 via a third-party bmp180.py driver and prints the readings every second.
#
# Buy this module: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bmp180-i2c-iic-digital-atmospheric-pressure-temperature-altitude-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BMP180 - Pico MicroPython
# Library: bmp180.py from Sebastian Wallkoetter (search GitHub).

from machine import Pin, I2C
from bmp180 import BMP180
import time

i2c = I2C(0, scl=Pin(5), sda=Pin(4), freq=400_000)
bmp = BMP180(i2c)
bmp.oversample_sett = 2
bmp.baseline = 101325   # sea-level pressure in Pa

while True:
    print("Temp:     {:.2f} C".format(bmp.temperature))
    print("Pressure: {:.2f} hPa".format(bmp.pressure / 100))
    print("Altitude: {:.2f} m\n".format(bmp.altitude))
    time.sleep(1)
