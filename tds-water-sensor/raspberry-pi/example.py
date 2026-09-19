# Python example for Raspberry Pi using an ADS1115 ADC to read the sensor voltage on A0, average samples, apply temperature compensation, and print TDS ppm.
#
# Buy this module: https://shillehtek.com/products/tds-water-sensor-module-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tds-water-sensor-module-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# Analog TDS Meter - Raspberry Pi + ADS1115 Example
# A->ADS1115 A0, +->3.3V, -->GND
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board, busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1
chan = AnalogIn(ads, ADS.P0)

WATER_TEMP = 25.0

def tds_ppm(volts, temp_c):
    v = volts / (1.0 + 0.02 * (temp_c - 25.0))
    return (133.42 * v**3 - 255.86 * v**2 + 857.39 * v) * 0.5

print("TDS meter ready - dip the probe")
try:
    while True:
        volts = sum(chan.voltage for _ in range(15)) / 15
        print(f"V: {volts:.3f} | TDS: {tds_ppm(volts, WATER_TEMP):.0f} ppm")
        time.sleep(1)
except KeyboardInterrupt:
    print("Stopped by user")
