# Run on a Raspberry Pi Pico: initialize UART and I2C, read compensated temperature/pressure/humidity from a BME280, and print the readings to the USB serial port once per second.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-bme280-save-data-to-pc
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import machine
from machine import I2C, Pin
import time
import uos

import bme280

# need this UART to read from BME and be able to send data to local computer
uart = machine.UART(0, baudrate=115200)
uart.init(115200, bits=8, parity=None, stop=1, tx=Pin(0), rx=Pin(1))
uos.dupterm(uart)
i2c=I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
bme = bme280.BME280(i2c=i2c)

while True:
    temperature, pressure, humidity = bme.read_compensated_data()
    print('{:.1f} C,{:.1f} %,{:.1f} hPa'.format(temperature/100, humidity/1024, pressure/25600))
    time.sleep(1)
