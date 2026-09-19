# Uses an ADS1115 I2C ADC (via Adafruit Blinka on a Raspberry Pi) to sample the sensor voltage, compute the RMS value over a short window, and print the measured AC mains voltage.
#
# Buy this module: https://shillehtek.com/products/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import math
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

# pip3 install adafruit-circuitpython-ads1x15

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.data_rate = 860          # fastest rate - needed for 50/60 Hz
chan = AnalogIn(ads, ADS.P0)

CAL = 250.0                  # tune against a multimeter

def read_rms(window_s=0.2):
    samples = []
    end = time.monotonic() + window_s
    while time.monotonic() < end:
        samples.append(chan.voltage)
    mean = sum(samples) / len(samples)
    var = sum((v - mean) ** 2 for v in samples) / len(samples)
    return math.sqrt(var) * CAL

while True:
    print("AC voltage: {:.1f} V".format(read_rms()))
    time.sleep(1)
