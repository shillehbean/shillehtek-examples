# Reads the divided pack voltage on a Raspberry Pi using an ADS1115 ADC over I2C, multiplies by the divider ratio, and prints the pack voltage periodically.
#
# Buy this module: https://shillehtek.com/products/12V
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3s-12v-18650-lithium-battery-protection-board-11-1v-12-6v-balanced-25a-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Raspberry Pi has no built-in ADC -- use an MCP3008 or ADS1115.
# Example uses ADS1115 over I2C with a 470k/100k voltage divider.

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
chan = AnalogIn(ads, ADS.P0)

DIVIDER_RATIO = (470.0 + 100.0) / 100.0  # = 5.7

try:
    while True:
        v_adc = chan.voltage
        v_pack = v_adc * DIVIDER_RATIO
        print("Pack: {:.2f} V".format(v_pack))
        time.sleep(1)
except KeyboardInterrupt:
    print("Stopped")
