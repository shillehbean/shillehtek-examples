# Configures the ADXL345 via smbus2 on a Raspberry Pi, reads raw axis registers over I2C, converts values to signed g and then to m/s², and prints X/Y/Z in a loop.
#
# Buy this module: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# ADXL345 - Raspberry Pi I2C Example
# Install: sudo apt install python3-smbus
# Wiring: SDA -> GPIO 2, SCL -> GPIO 3, 3V3 -> 3.3V, GND -> GND, CS -> 3.3V

import smbus2
import time

ADDR = 0x53          # default I2C address
POWER_CTL = 0x2D
DATA_FORMAT = 0x31
DATAX0 = 0x32
SCALE = 0.0039 * 9.80665  # +/-2g, full-res: 3.9 mg/LSB -> m/s^2

bus = smbus2.SMBus(1)

def setup():
    bus.write_byte_data(ADDR, DATA_FORMAT, 0x08)  # full-res, +/-2g
    bus.write_byte_data(ADDR, POWER_CTL, 0x08)    # measurement mode

def read_axes():
    raw = bus.read_i2c_block_data(ADDR, DATAX0, 6)
    x = int.from_bytes(raw[0:2], 'little', signed=True) * SCALE
    y = int.from_bytes(raw[2:4], 'little', signed=True) * SCALE
    z = int.from_bytes(raw[4:6], 'little', signed=True) * SCALE
    return x, y, z

setup()
try:
    while True:
        x, y, z = read_axes()
        print("X: {:6.2f}  Y: {:6.2f}  Z: {:6.2f}  m/s^2".format(x, y, z))
        time.sleep(0.2)
except KeyboardInterrupt:
    print("Stopped by user")
