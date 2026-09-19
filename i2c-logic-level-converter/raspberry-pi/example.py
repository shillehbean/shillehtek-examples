# Performs an I2C bus scan on a Raspberry Pi through the level shifter using smbus2 and lists detected device addresses.
#
# Buy this module: https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/iic-i2c-logic-level-converter-pre-soldered-bi-directional
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Raspberry Pi I2C scan through the level shifter
# Requires: sudo raspi-config -> Interface Options -> I2C enabled
# Install: sudo apt install i2c-tools
#          pip install smbus2

from smbus2 import SMBus

bus = SMBus(1)
print("Scanning I2C bus (through level shifter)...")
found = []
for addr in range(1, 128):
    try:
        bus.read_byte(addr)
        found.append(hex(addr))
    except OSError:
        pass
print("Devices:", found if found else "none")
bus.close()
