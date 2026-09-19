# Runs on a Raspberry Pi Pico under MicroPython to read all four ADS1115 channels over I2C and print raw ADC counts and converted voltages.
#
# Buy this module: https://shillehtek.com/products/shillehtek-ads-1115-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1115-4-channel-i2c-iic-analog-to-digital-adc-pga-16-bit-16-byte-converter
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ADS1115 on Raspberry Pi Pico via I2C0 (GP0 SDA, GP1 SCL)
# Upload an ads1x15.py driver to the Pico filesystem first.

from machine import I2C, Pin
from ads1x15 import ADS1115
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
print("I2C scan:", [hex(d) for d in i2c.scan()])

# gain=1 -> +/- 4.096V full scale
adc = ADS1115(i2c, address=0x48, gain=1)

while True:
    for channel in range(4):
        raw = adc.read(channel1=channel)
        volts = raw * 4.096 / 32767
        print("A{}: raw={}  {:.4f} V".format(channel, raw, volts))
    print("-" * 30)
    time.sleep(1)
