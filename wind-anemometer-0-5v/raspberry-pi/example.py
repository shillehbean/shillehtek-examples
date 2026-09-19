# Uses a Raspberry Pi with an ADS1115 ADC to read the anemometer signal via I2C, applies the divider correction, converts the voltage to wind speed, and prints the measurements.
#
# Buy this module: https://shillehtek.com/products/anemometer-wind-speed-0-5v-analog-output
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/anemometer-wind-speed-0-5v-analog-output-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# Wind Speed Sensor (0-5V Anemometer) - Raspberry Pi + ADS1115 Example
# Blue signal -> 10k/20k divider -> ADS1115 A0, SDA/SCL -> GPIO 2/3
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

DIVIDER_RATIO = 1.5   # (10k + 20k) / 20k

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1          # +/-4.096V range covers the divided 0-3.33V signal
channel = AnalogIn(ads, ADS.P0)

try:
    while True:
        signal_volts = channel.voltage * DIVIDER_RATIO
        wind_ms = signal_volts * 6.0
        wind_mph = wind_ms * 2.237

        print("Signal: {:.2f} V | Wind: {:.1f} m/s ({:.1f} mph)".format(
            signal_volts, wind_ms, wind_mph))
        time.sleep(1)

except KeyboardInterrupt:
    print("Measurement stopped by user")
