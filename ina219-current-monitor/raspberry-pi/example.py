# Demonstrates using the Adafruit CircuitPython INA219 library on a Raspberry Pi to read bus voltage, shunt voltage, current and power over I2C and print formatted measurements every second.
#
# Buy this module: https://shillehtek.com/products/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install adafruit-circuitpython-ina219
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

import time
import board, busio
from adafruit_ina219 import INA219

i2c = busio.I2C(board.SCL, board.SDA)
ina = INA219(i2c)

while True:
    bus = ina.bus_voltage           # V
    shunt = ina.shunt_voltage       # V
    current = ina.current           # mA
    power = ina.power               # W
    print(f"Bus: {bus:.2f}V  Shunt: {shunt*1000:.2f}mV  "
          f"I: {current:.2f}mA  P: {power*1000:.2f}mW")
    time.sleep(1)
