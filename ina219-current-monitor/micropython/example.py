# Shows how to use a MicroPython INA219 driver on a Pico (specifying a 0.1Ω shunt) to configure the sensor and print voltage, current and power periodically over I2C.
#
# Buy this module: https://shillehtek.com/products/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-219-ina219-i2c-bi-directional-current-power-monitoring-sensor-module-with-soldering-and-foam-manual
# More examples: https://github.com/shillehtek/examples
#

# INA219 on Pico - MicroPython
# Install: copy ina219.py from robert-hh/INA219 (or pip install via mip)

from machine import I2C, Pin
from ina219 import INA219
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)
ina = INA219(0.1, i2c)
ina.configure(voltage_range=ina.RANGE_16V, gain=ina.GAIN_AUTO)

while True:
    print('Bus: {:.2f}V  Current: {:.2f}mA  Power: {:.2f}mW'.format(
        ina.voltage(), ina.current(), ina.power()))
    time.sleep(1)
