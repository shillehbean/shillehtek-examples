# Uses CircuitPython on a Raspberry Pi with the adafruit-circuitpython-ads1x15 library to read all four ADS1115 channels and print raw counts and voltages once per second.
#
# Buy this module: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1115-4-channel-i2c-iic-analog-to-digital-adc-pga-16-bit-16-byte-converter
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ADS1115 on Raspberry Pi via I2C
# Install: pip install adafruit-circuitpython-ads1x15
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c, address=0x48)
ads.gain = 1  # +/- 4.096V

chans = [AnalogIn(ads, ADS.P0),
         AnalogIn(ads, ADS.P1),
         AnalogIn(ads, ADS.P2),
         AnalogIn(ads, ADS.P3)]

while True:
    for i, ch in enumerate(chans):
        print(f"A{i}: raw={ch.value}  {ch.voltage:.4f} V")
    print("-" * 30)
    time.sleep(1)
