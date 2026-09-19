# Raspberry Pi Python script using smbus2 to configure the HMC5883L over I2C, read raw X/Y/Z axes, and compute a continuous compass heading in radians/degrees.
#
# Buy this module: https://shillehtek.com/products/hmc5883l-gy-273-magnetometer-compass-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hmc5883l-gy-273-magnetometer-compass-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# HMC5883L (GY-273) Compass - Raspberry Pi Example
# SDA -> GPIO 2 (pin 3), SCL -> GPIO 3 (pin 5), VCC -> 3.3V (pin 1)
# Setup: enable I2C in raspi-config, then: pip3 install smbus2

import math
import time
from smbus2 import SMBus

ADDR = 0x1E   # HMC5883L (0x0D would be a QMC5883L - different chip!)

bus = SMBus(1)

# Config A: 8 samples averaged, 15 Hz output  -> 0x70
bus.write_byte_data(ADDR, 0x00, 0x70)
# Config B: gain +/-1.3 gauss (default)       -> 0x20
bus.write_byte_data(ADDR, 0x01, 0x20)
# Mode: continuous measurement                -> 0x00
bus.write_byte_data(ADDR, 0x02, 0x00)
time.sleep(0.1)

def read_axes():
    # Data registers start at 0x03, order is X, Z, Y (big endian)
    data = bus.read_i2c_block_data(ADDR, 0x03, 6)
    def s16(hi, lo):
        v = (hi << 8) | lo
        return v - 65536 if v > 32767 else v
    x = s16(data[0], data[1])
    z = s16(data[2], data[3])
    y = s16(data[4], data[5])
    return x, y, z

print("Compass ready - rotate the board slowly (Ctrl+C to stop)")

try:
    while True:
        x, y, z = read_axes()

        heading = math.atan2(y, x)
        # Add your local magnetic declination here (radians)
        if heading < 0:
            heading += 2 * math.pi

        print("X: {:6d}  Y: {:6d}  Z: {:6d}  |  Heading: {:5.1f} deg".format(
            x, y, z, math.degrees(heading)))
        time.sleep(0.5)

except KeyboardInterrupt:
    print("Stopped by user")
finally:
    bus.close()
