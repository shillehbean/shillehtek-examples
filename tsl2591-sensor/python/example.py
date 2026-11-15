# Runs under Python on Raspberry Pi using the Adafruit CircuitPython TSL2591 library to print lux, visible, infrared, and full-spectrum values, with overflow handling.
#
# Buy this module: https://shillehtek.com/products/tsl2591-light-sensor-presoldered-purple-breakout-single
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tsl2591-light-sensor-presoldered-purple-breakout-single-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# TSL2591 light sensor on Raspberry Pi (I2C bus 1)
# Install once: pip3 install adafruit-circuitpython-tsl2591   (enable I2C in raspi-config)
import time
import board
import adafruit_tsl2591

i2c = board.I2C()                        # GPIO 2 = SDA, GPIO 3 = SCL
sensor = adafruit_tsl2591.TSL2591(i2c)   # fixed address 0x29

sensor.gain = adafruit_tsl2591.GAIN_MED                            # 25x suits indoor light
sensor.integration_time = adafruit_tsl2591.INTEGRATIONTIME_300MS   # longer = more sensitive

while True:
    try:
        print(f"Lux: {sensor.lux:.2f}   Visible: {sensor.visible}   "
              f"IR: {sensor.infrared}   Full: {sensor.full_spectrum}")
    except RuntimeError:
        print("Sensor overflow - lower the gain")    # raised when a channel saturates
    time.sleep(1.0)
