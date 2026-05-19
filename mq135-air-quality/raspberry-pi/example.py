# Runs on a Raspberry Pi using an ADS1115 I2C ADC to measure the MQ-135 analog output and a GPIO input for DO, printing the measured voltage and whether the DO alarm is active.
#
# Buy this module: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# MQ-135 + ADS1115 on Raspberry Pi
# pip install adafruit-circuitpython-ads1x15 RPi.GPIO

import time
import board, busio
import RPi.GPIO as GPIO
from adafruit_ads1x15.ads1115 import ADS1115
from adafruit_ads1x15.analog_in import AnalogIn

DO_PIN = 17
GPIO.setmode(GPIO.BCM)
GPIO.setup(DO_PIN, GPIO.IN)

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS1115(i2c)
ao  = AnalogIn(ads, 0)

try:
    while True:
        v = ao.voltage
        d = "ALARM" if GPIO.input(DO_PIN) == 0 else "OK"
        print("AO={:.3f} V    DO={}".format(v, d))
        time.sleep(0.5)
except KeyboardInterrupt:
    GPIO.cleanup()
