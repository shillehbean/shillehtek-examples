# Reads the KY-018 through an ADS1115 ADC on a Raspberry Pi using CircuitPython, converts the reading to volts and prints a bright/dim/dark classification.
#
# Buy this module: https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/photoresistor-light-sensor-ky-018-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# KY-018 Photoresistor - Raspberry Pi + ADS1115 Example
# S -> ADS1115 A0, SDA/SCL -> GPIO 2/3, VCC -> 3.3V
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1                       # +/-4.096V range
channel = AnalogIn(ads, ADS.P0)

try:
    while True:
        volts = channel.voltage    # 0-3.3V, higher = brighter

        if volts > 2.3:
            state = "bright"
        elif volts > 1.0:
            state = "dim"
        else:
            state = "dark"

        print("Light level: {:.2f} V ({})".format(volts, state))
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
