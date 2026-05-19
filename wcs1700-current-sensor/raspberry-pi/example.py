# Uses an ADS1115 ADC on a Raspberry Pi to auto-zero the WCS1700 analog output and print the measured current in amps.
#
# Buy this module: https://shillehtek.com/products/wcs1700-70a-hall-current-sensor-module-overcurrent-detect
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wcs1700-70a-hall-current-sensor-module-overcurrent-detect-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# WCS1700 + ADS1115 on Raspberry Pi
# pip install adafruit-circuitpython-ads1x15

import time
import board, busio
from adafruit_ads1x15.ads1115 import ADS1115
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS1115(i2c)
ch  = AnalogIn(ads, 0)            # WCS1700 Aout -> A0

SENSITIVITY = 0.032               # V/A

# Auto-zero
samples = [ch.voltage for _ in range(200)]
offset = sum(samples) / len(samples)
print("Zero offset: {:.3f} V".format(offset))

while True:
    v = ch.voltage
    amps = (v - offset) / SENSITIVITY
    print("V={:.3f}  I={:.2f} A".format(v, amps))
    time.sleep(0.25)
