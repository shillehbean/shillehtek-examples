# Uses an ADS1115 I²C ADC on a Raspberry Pi to read the AD8232 OUTPUT (ADS A0) at a high data rate and prints raw values every ~2 ms for plotting or logging.
#
# Buy this module: https://shillehtek.com/products/ecg-electrode-pads-ad8232-5-pack
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ecg-electrode-pads-ad8232-5-pack-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

# The Pi has no analog input: AD8232 OUTPUT -> ADS1115 A0
# pip3 install adafruit-circuitpython-ads1x15

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.data_rate = 860              # fastest rate for waveform detail
chan = AnalogIn(ads, ADS.P0)

while True:
    print(chan.value)            # pipe to a plotter or log to a file
    time.sleep(0.002)
