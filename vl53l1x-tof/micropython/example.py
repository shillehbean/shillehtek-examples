# MicroPython example that initializes I2C (SDA=4, SCL=5), scans for the VL53L1X, then continuously reads and prints distance measurements in millimeters.
#
# Buy this module: https://shillehtek.com/products/vl53l1x-tof-sensor-4m-pre-soldered-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vl53l1x-tof-sensor-4m-pre-soldered-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import I2C, Pin
import time
from vl53l1x import VL53L1X   # copy vl53l1x.py driver to the board

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])  # expect 0x29

tof = VL53L1X(i2c)

while True:
    mm = tof.read()
    print("Distance:", mm, "mm")
    time.sleep(0.1)
