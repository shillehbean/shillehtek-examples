# Python script for Raspberry Pi using an ADS1115 over I2C: reads the sensor on ADS1115 channel A0, converts the measured voltage to millivolts, estimates UV index as mV/100, and prints values once per second.
#
# Buy this module: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/uv-sensor-guva-s12sd-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# GUVA-S12SD UV Sensor - Raspberry Pi + ADS1115 Example
# The Pi has no analog inputs, so an ADS1115 reads SIG over I2C.
# SIG -> ADS1115 A0, SDA -> GPIO 2, SCL -> GPIO 3
# Install the library first:
#   pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

# I2C bus on GPIO 2 (SDA) / GPIO 3 (SCL)
i2c = busio.I2C(board.SCL, board.SDA)

# ADS1115 at default address 0x48, sensor SIG on channel A0
ads = ADS.ADS1115(i2c)
ads.gain = 2  # +/-2.048V full scale covers the 0-1V output with headroom
channel = AnalogIn(ads, ADS.P0)

try:
    while True:
        millivolts = channel.voltage * 1000

        # Approximate solar UV Index: mV / 100
        uv_index = millivolts / 100

        print("Voltage: {:.0f} mV | UV Index: {:.1f}".format(millivolts, uv_index))
        time.sleep(1)

except KeyboardInterrupt:
    print("Measurement stopped by user")
