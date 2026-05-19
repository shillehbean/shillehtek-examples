# Uses an ADS1115 I2C ADC to read the midpoint of the 30k/10k divider and prints the calculated XL4015 rail voltage every 0.5 seconds.
#
# Buy this module: https://shillehtek.com/products/dc-dc-xl4015-adjustable-step-down-module-4-38v-5a-96-high-efficiency
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dc-dc-xl4015-adjustable-step-down-module-4-38v-5a-96-high-efficiency-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Use ADS1115 (16-bit ADC) to monitor XL4015 output
# Same divider: 30k + 10k from OUT+ to GND, ADS A0 reads middle

import time
import board, busio
from adafruit_ads1x15.ads1115 import ADS1115
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS1115(i2c)
chan = AnalogIn(ads, 0)

DIV_RATIO = 4.0  # 30k+10k / 10k

while True:
    rail = chan.voltage * DIV_RATIO
    print(f"Rail: {rail:.2f} V")
    time.sleep(0.5)
