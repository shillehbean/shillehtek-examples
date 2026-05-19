# Use an ADS1115 I2C ADC on a Raspberry Pi to read the EMG channel as voltage and print the value with a simple threshold-based flex indicator.
#
# Buy this module: https://shillehtek.com/products/emg-muscle-signal-sensor-module-kit-for-arduino-robotics
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/emg-muscle-signal-sensor-module-kit-for-arduino-robotics-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# ShillehTek EMG Sensor - Raspberry Pi Example
# Reads the EMG module via an ADS1115 I2C ADC on channel A0.
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1  # +/- 4.096V range
chan = AnalogIn(ads, ADS.P0)

FLEX_THRESHOLD_V = 1.2  # tune this to your resting baseline

try:
    while True:
        voltage = chan.voltage
        label = "FLEX!" if voltage > FLEX_THRESHOLD_V else ""
        print("EMG: {:.3f} V  {}".format(voltage, label))
        time.sleep(0.02)
except KeyboardInterrupt:
    print("Stopped")
