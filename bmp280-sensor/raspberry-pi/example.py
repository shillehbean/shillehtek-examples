# Uses the Adafruit CircuitPython BMP280 driver on a Raspberry Pi to read and print temperature, pressure, and altitude once per second.
#
# Buy this module: https://shillehtek.com/products/shillehtek-bmp280-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bmp280-i2c-iic-digital-atmospheric-pressure-temperature-altitude-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# BMP280 - Raspberry Pi Python Example
# Install: sudo pip3 install adafruit-circuitpython-bmp280

import time
import board
import adafruit_bmp280

i2c = board.I2C()
bmp = adafruit_bmp280.Adafruit_BMP280_I2C(i2c, address=0x76)
bmp.sea_level_pressure = 1013.25

while True:
    print(f"Temp: {bmp.temperature:.2f} C")
    print(f"Pressure: {bmp.pressure:.2f} hPa")
    print(f"Altitude: {bmp.altitude:.2f} m\n")
    time.sleep(1)
