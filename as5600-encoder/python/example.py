# Poll the AS5600 from a Raspberry Pi via smbus2 to report magnet status and print the raw 12-bit angle in degrees in a loop.
#
# Buy this module: https://shillehtek.com/products/as5600-magnetic-encoder-pre-soldered-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/as5600-magnetic-encoder-pre-soldered-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# AS5600 magnetic encoder on Raspberry Pi (I2C bus 1)
# Install once: sudo apt install python3-smbus2   (enable I2C in raspi-config)
import time
from smbus2 import SMBus

AS5600_ADDR = 0x36
REG_STATUS = 0x0B       # bit 5 = magnet detected, bit 4 = too weak, bit 3 = too strong
REG_RAW_ANGLE = 0x0C    # two bytes, high byte first

with SMBus(1) as bus:
    status = bus.read_byte_data(AS5600_ADDR, REG_STATUS)
    if not status & 0x20:
        print("No magnet detected - center it over the chip")
    if status & 0x10:
        print("Magnet too weak - move it closer")
    if status & 0x08:
        print("Magnet too strong - move it away")

    while True:
        high, low = bus.read_i2c_block_data(AS5600_ADDR, REG_RAW_ANGLE, 2)
        raw = ((high << 8) | low) & 0x0FFF          # 12-bit value, 0-4095
        degrees = raw * 360.0 / 4096.0
        print(f"Raw: {raw:4d}   Angle: {degrees:6.1f} deg")
        time.sleep(0.1)
