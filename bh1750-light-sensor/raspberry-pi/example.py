# Reads BH1750 via I2C on a Raspberry Pi using smbus2 in continuous high-resolution mode and prints lux values.
#
# Buy this module: https://shillehtek.com/products/shillehtek-gy-302-bh1750-pre-soldered-light-intensity-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bh1750-pre-soldered-light-intensity-module
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BH1750 on Raspberry Pi via I2C
# Install: pip install smbus2
# Enable I2C: sudo raspi-config -> Interface Options -> I2C

import smbus2
import time

BH1750_ADDR = 0x23
CONT_H_RES  = 0x10   # continuous 1-lux resolution

bus = smbus2.SMBus(1)
bus.write_byte(BH1750_ADDR, CONT_H_RES)
time.sleep(0.2)  # first conversion

while True:
    data = bus.read_i2c_block_data(BH1750_ADDR, 0x00, 2)
    raw  = (data[0] << 8) | data[1]
    lux  = raw / 1.2
    print(f"Light: {lux:.1f} lx")
    time.sleep(1)
