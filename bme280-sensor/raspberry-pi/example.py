# Uses smbus2 and the bme280 Python module on a Raspberry Pi to load calibration parameters and print temperature, humidity, and pressure samples every second.
#
# Buy this module: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bme280-environmental-sensor-raspberry-pi-arduino-esp32-i2c-humidity-pressure-and-temperature-measurement
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BME280 on Raspberry Pi via I2C
# Install: pip install RPi.bme280 smbus2
# Enable I2C first: sudo raspi-config -> Interface Options -> I2C

import smbus2
import bme280
import time

port = 1           # I2C bus 1 on modern Pi
address = 0x76     # 0x77 if SDO is tied high
bus = smbus2.SMBus(port)

calibration_params = bme280.load_calibration_params(bus, address)

while True:
    data = bme280.sample(bus, address, calibration_params)
    print(f"Temp: {data.temperature:.2f} C")
    print(f"Humidity: {data.humidity:.2f} %")
    print(f"Pressure: {data.pressure:.2f} hPa")
    print("-" * 30)
    time.sleep(1)
