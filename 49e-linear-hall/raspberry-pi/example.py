# Uses an ADS1115 on I2C to read the sensor output on a Raspberry Pi, calibrates a zero point, converts voltage to gauss, and logs field strength and pole to the console.
#
# Buy this module: https://shillehtek.com/products/linear-hall-effect-sensor-49e-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/linear-hall-effect-sensor-49e-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 49E Linear Hall Effect Sensor - Raspberry Pi + ADS1115 Example
# OUT -> ADS1115 A0, SDA/SCL -> GPIO 2/3, VCC -> 3.3V
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

MV_PER_GAUSS = 0.9   # ~0.9 mV/G at 3.3V supply

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1
channel = AnalogIn(ads, ADS.P0)

def read_volts(samples):
    total = 0.0
    for _ in range(samples):
        total += channel.voltage
        time.sleep(0.002)
    return total / samples

print("Calibrating - keep magnets away...")
time.sleep(1)
zero = read_volts(100)
print("Zero point: {:.3f} V. Bring a magnet close!".format(zero))

try:
    while True:
        volts = read_volts(20)
        gauss = (volts - zero) * 1000 / MV_PER_GAUSS

        if gauss > 15:
            pole = "south pole"
        elif gauss < -15:
            pole = "north pole"
        else:
            pole = "no field"

        print("OUT: {:.3f} V | ~{:.0f} G ({})".format(volts, gauss, pole))
        time.sleep(0.3)
except KeyboardInterrupt:
    print("Stopped by user")
