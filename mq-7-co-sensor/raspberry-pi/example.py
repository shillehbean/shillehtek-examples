# Uses an ADS1115 on I2C (Raspberry Pi) to read the MQ-7 analog channel, applies a divider compensation, and prints the measured sensor voltage continuously.
#
# Buy this module: https://shillehtek.com/products/mq-7-co-gas-sensor-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-7-co-gas-sensor-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

# pip3 install adafruit-circuitpython-ads1x15
# MQ-7 A0 -> 10k/20k divider -> ADS1115 A0

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
chan = AnalogIn(ads, ADS.P0)

DIVIDER = 1.5  # recovers the pre-divider voltage

print("MQ-7 warming up - readings stabilize after several minutes")
while True:
    v_sensor = chan.voltage * DIVIDER
    print(f"Sensor voltage: {v_sensor:.2f} V")
    time.sleep(1)
