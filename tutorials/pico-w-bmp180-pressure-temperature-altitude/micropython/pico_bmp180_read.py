# Reads temperature, pressure, and altitude from a BMP180 over I2C on a Pico W, converts temperature to Fahrenheit, and prints the values in a loop.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-bmp180-pressure-temperature-altitude
# Parts used: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, I2C
from bmp085 import BMP180
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=40000)

bmp = BMP180(i2c)
bmp.oversample = 2
bmp.sealevel = 1010.5

while True:
    tempC = bmp.temperature  # get the temperature in degree celsius
    pres_hPa = bmp.pressure  # get the pressure in hpa
    altitude = bmp.altitude  # get the altitude
    temp_f = (tempC * (9/5) + 32)  # convert the temperature value in fahrenheit
    print(str(tempC) + "°C " + str(temp_f) + "°F " + str(pres_hPa) + "hPa " + str(altitude))
    time.sleep_ms(100)  # delay of 100 milliseconds
