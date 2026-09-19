# Uses an ADS1115 on a Raspberry Pi with a GPIO power pin to measure probe voltage, classifies it as dry/low/HIGH water, and prints the measured voltage every 3 seconds.
#
# Buy this module: https://shillehtek.com/products/sensor-rain-water-level-arduino-raspberry-pi-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sensor-rain-water-level-arduino-raspberry-pi-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# Water Level Sensor - Raspberry Pi + ADS1115 Example (GPIO-powered)
# S -> ADS1115 A0, + -> GPIO 17 (pin 11), - -> GND
# Install: pip3 install adafruit-circuitpython-ads1x15

import time
import board
import busio
import RPi.GPIO as GPIO
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

POWER_PIN = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(POWER_PIN, GPIO.OUT, initial=GPIO.LOW)

i2c = busio.I2C(board.SCL, board.SDA)
ads = ADS.ADS1115(i2c)
ads.gain = 1
channel = AnalogIn(ads, ADS.P0)

def read_level():
    GPIO.output(POWER_PIN, GPIO.HIGH)   # energize the probe
    time.sleep(0.02)                    # settle
    volts = channel.voltage
    GPIO.output(POWER_PIN, GPIO.LOW)    # off - no electrolysis
    return volts

try:
    while True:
        volts = read_level()

        if volts < 0.3:
            state = "dry"
        elif volts < 1.5:
            state = "low water"
        else:
            state = "HIGH water!"

        print("Signal: {:.2f} V ({})".format(volts, state))
        time.sleep(3)

except KeyboardInterrupt:
    print("Stopped by user")
finally:
    GPIO.cleanup()
