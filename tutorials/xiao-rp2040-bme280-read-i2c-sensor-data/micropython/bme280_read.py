# Initializes I2C on the XIAO RP2040, creates a BME280 sensor object, and continuously prints temperature, pressure, and humidity readings.
#
# Full tutorial: https://shillehtek.com/blogs/news/xiao-rp2040-bme280-read-i2c-sensor-data
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/seeed-studio-xiao-rp2040-pre-soldered-with-usb-to-usb-c-cable
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, I2C        #importing relevant modules & classes
from time import sleep
import bme280       #importing BME280 library

i2c=I2C(1,sda=Pin(6), scl=Pin(7), freq=400000)    #initializing the I2C method 


while True:
  bme = bme280.BME280(i2c=i2c)          #BME280 object created
  print(bme.values)
  sleep(1)           #delay of 10s
