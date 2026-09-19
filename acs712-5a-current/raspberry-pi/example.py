# Raspberry Pi Python script using an ADS1115 ADC to read the ACS712 (with a voltage divider), calibrate the zero offset, and print measured voltage and calculated DC current.
#
# Buy this module: https://shillehtek.com/products/acs712-current-sensor-5a-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/acs712-current-sensor-5a-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# ACS712 5A Current Sensor - Raspberry Pi + ADS1115 Example (DC current)
# OUT -> 10k/20k divider -> ADS1115 A0, SDA/SCL -> GPIO 2/3
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

SENSITIVITY = 0.185    # volts per amp (5A version)
DIVIDER = 1.5          # (10k + 20k) / 20k

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1           # +/-4.096V range
channel = AnalogIn(ads, ADS.P0)

def read_volts(samples):
    total = 0.0
    for _ in range(samples):
        total += channel.voltage
        time.sleep(0.002)
    return total / samples * DIVIDER

print("Calibrating zero point, keep load OFF...")
zero = read_volts(300)
print("Zero = {:.3f} V. Measuring...".format(zero))

try:
    while True:
        volts = read_volts(100)
        amps = (volts - zero) / SENSITIVITY
        print("OUT: {:.3f} V | Current: {:.3f} A".format(volts, amps))
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Stopped by user")
