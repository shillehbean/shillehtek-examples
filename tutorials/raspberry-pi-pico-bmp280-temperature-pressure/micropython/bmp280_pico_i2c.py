# Initializes I2C on a Raspberry Pi Pico, creates a BMP280 sensor object, and prints temperature and pressure readings once per second.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-bmp280-temperature-pressure
# Parts used: https://shillehtek.com/products/shillehtek-bmp280-pre-soldered
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, I2C
from utime import sleep
from bmp280 import BMP280I2C

# I2C0 on the Pico: SDA=GP0, SCL=GP1
i2c0 = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)

# Address may differ depending on your specific sensor module
bmp280_i2c = BMP280I2C(i2c0, 0x76)

while True:
    readout = bmp280_i2c.measurements
    print(f"Temperature: {readout['t']} C")
    print(f"Pressure: {readout['p']} hPa")
    sleep(1)
