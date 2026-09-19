# Uses Adafruit's CircuitPython BMP085 library on a Raspberry Pi to read and print BMP180 temperature, pressure, and altitude values once per second.
#
# Buy this module: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bmp180-i2c-iic-digital-atmospheric-pressure-temperature-altitude-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# BMP180 - Raspberry Pi Python Example
# Install: sudo pip3 install adafruit-circuitpython-bmp085

import time
import board
import adafruit_bmp085

i2c = board.I2C()
bmp = adafruit_bmp085.Adafruit_BMP085(i2c)

while True:
    print(f"Temp:     {bmp.temperature:.2f} C")
    print(f"Pressure: {bmp.pressure:.2f} hPa")
    print(f"Altitude: {bmp.altitude:.2f} m\n")
    time.sleep(1)
