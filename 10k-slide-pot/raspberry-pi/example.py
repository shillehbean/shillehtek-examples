# Python example for Raspberry Pi using an ADS1115 I²C ADC to read the pot on A0, calculate voltage/percent, and print a simple text bar graph.
#
# Buy this module: https://shillehtek.com/products/slide-potentiometer-module-10k-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/slide-potentiometer-module-10k-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 10K Slide Potentiometer - Raspberry Pi + ADS1115 Example
# OTA->ADS1115 A0, SDA/SCL->GPIO 2/3, VCC->3.3V
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1                       # +/-4.096V range
chan = AnalogIn(ads, ADS.P0)

print("Slide the fader!")
try:
    while True:
        volts = chan.voltage
        percent = max(0, min(100, volts / 3.3 * 100))
        bar = "#" * int(percent / 5)
        print("{:5.3f} V | {:5.1f} % | {}".format(volts, percent, bar))
        time.sleep(0.1)
except KeyboardInterrupt:
    print("Stopped by user")
