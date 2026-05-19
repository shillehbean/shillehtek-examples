# Example for Raspberry Pi Pico running MicroPython with Kevin McAleer's vl53l0x driver to start the sensor and print periodic distance readings over USB serial.
#
# Buy this module: https://shillehtek.com/products/gy-vl53l0xv2-laser-ranging-tof-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-vl53l0xv2-laser-ranging-tof-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

# VL53L0X on Raspberry Pi Pico (MicroPython)
# Wiring: VCC->3V3, GND->GND, SCL->GP1, SDA->GP0
# Needs the VL53L0X MicroPython driver by Kevin McAleer:
# Copy vl53l0x.py from https://github.com/kevinmcaleer/vl53l0x_micropython
# onto the Pico filesystem.

from machine import I2C, Pin
from vl53l0x import VL53L0X
import time

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])

tof = VL53L0X(i2c)
tof.start()

while True:
    distance = tof.read()
    print("Distance:", distance, "mm")
    time.sleep_ms(100)
