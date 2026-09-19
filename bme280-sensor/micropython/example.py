# Uses a MicroPython bme280 driver on a Raspberry Pi Pico (I2C0) to read compensated temperature, pressure, and humidity values and print them in a loop.
#
# Buy this module: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bme280-environmental-sensor-raspberry-pi-arduino-esp32-i2c-humidity-pressure-and-temperature-measurement
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BME280 on Raspberry Pi Pico via I2C0 (GP0 SDA, GP1 SCL)
# Upload a bme280.py driver module to the Pico filesystem first.

from machine import Pin, I2C
import bme280
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=100000)
print("I2C scan:", [hex(d) for d in i2c.scan()])

sensor = bme280.BME280(i2c=i2c, address=0x76)

while True:
    t, p, h = sensor.read_compensated_data()
    print("Temp:    {:.2f} C".format(t / 100))
    print("Pressure: {:.2f} hPa".format(p / 25600))
    print("Humidity: {:.2f} %".format(h / 1024))
    print("-" * 30)
    time.sleep(1)
