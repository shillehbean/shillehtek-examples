# Initialize the ADS1115 over I2C, read analog channel P0 (MQ-135), and print the sensor voltage once per second.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ads1115-read-mq135-voltage
# Parts used: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
#             https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn


i2c = busio.I2C(board.SCL, board.SDA)

# Create the ADS object and specify the gain
ads = ADS.ADS1115(i2c)
ads.gain = 1
chan = AnalogIn(ads, ADS.P0)

# Continuously print the values
while True:
    print(f"MQ-135 Voltage: {chan.voltage}V")
    time.sleep(1)
