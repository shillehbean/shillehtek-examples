# Initializes the I2C-connected BME280 sensor and prints temperature, humidity, pressure, and altitude once per second.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-bme280-measure-altitude
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import board
import busio
from adafruit_bme280 import basic as adafruit_bme280

# Create sensor object, using the board's default I2C bus.
i2c = busio.I2C(board.GP1, board.GP0)  # SCL, SDA
# address can change based on bme device
# if 0x76 does not work try 0x77 :)
bme280 = adafruit_bme280.Adafruit_BME280_I2C(i2c, address=0x76)
# change this to match the location's pressure (hPa) at sea level
bme280.sea_level_pressure = 1009.9

while True:
    print("\nTemperature: %0.1f C" % bme280.temperature)
    print("Humidity: %0.1f %%" % bme280.relative_humidity)
    print("Pressure: %0.1f hPa" % bme280.pressure)
    print("Altitude = %0.2f meters" % bme280.altitude)
    time.sleep(1)
