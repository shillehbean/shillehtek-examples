# Uses an ADS1115 ADC on Raspberry Pi to read the divider voltage, calculates the thermistor resistance and converts it to temperature with the beta (Steinhart) equation, printing C and F periodically.
#
# Buy this module: https://shillehtek.com/products/10k-ntc-thermistor-temperature-sensor-mf52-103
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/10k-ntc-thermistor-temperature-sensor-mf52-103-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MF52-103 10K NTC Thermistor - Raspberry Pi + ADS1115 Example
# Divider: 3.3V - thermistor - ADS1115 A0 - 10k - GND
# Install: pip3 install adafruit-circuitpython-ads1x15

import time, math
import board, busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

VCC, SERIES_R, NOMINAL, B_COEFF = 3.3, 10000.0, 10000.0, 3950.0

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1
chan = AnalogIn(ads, ADS.P0)

def read_temp_c():
    volts = sum(chan.voltage for _ in range(10)) / 10
    r_ntc = SERIES_R * (VCC / volts - 1.0)
    steinhart = (math.log(r_ntc / NOMINAL) / B_COEFF
                 + 1.0 / (25.0 + 273.15))
    return 1.0 / steinhart - 273.15

print("MF52-103 thermistor ready")
try:
    while True:
        c = read_temp_c()
        print("Temperature: {:.1f} C / {:.1f} F".format(c, c * 9 / 5 + 32))
        time.sleep(1)
except KeyboardInterrupt:
    print("Stopped by user")
