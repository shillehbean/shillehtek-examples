# Python script for a Raspberry Pi using an ADS1115 I2C ADC to measure probe voltage, convert it to a moisture percentage using DRY/WET voltages, and print the readings periodically.
#
# Buy this module: https://shillehtek.com/products/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/soil-moisture-sensor-hygrometer-module-for-arduino-watering-kit-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Soil moisture + ADS1115 on Raspberry Pi
# pip install adafruit-circuitpython-ads1x15

import time
import board, busio
from adafruit_ads1x15.ads1115 import ADS1115
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS1115(i2c)
ao  = AnalogIn(ads, 0)

DRY = 3.20   # volts in air
WET = 1.30   # volts submerged

while True:
    v   = ao.voltage
    pct = max(0, min(100, int((DRY - v) * 100 / (DRY - WET))))
    print("V={:.3f}   Moisture={} %".format(v, pct))
    time.sleep(1)
