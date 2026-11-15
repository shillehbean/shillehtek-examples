# Uses Python with smbus2 to probe the CP2112 I2C bus; replace the example bus number with the adapter bus shown on your system.
#
# Buy this module: https://shillehtek.com/products/cp2112-usbc-i2c-smbus-adapter-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cp2112-usbc-i2c-smbus-adapter-presoldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# CP2112 USB to I2C adapter on Linux - scan the bus from Python with smbus2
# Install: sudo apt install python3-smbus2
# Find the bus number N with "i2cdetect -l", then run: sudo python3 cp2112_scan.py N
import sys
from smbus2 import SMBus

bus_number = int(sys.argv[1]) if len(sys.argv) > 1 else 1

found = []
with SMBus(bus_number) as bus:
    for address in range(0x08, 0x78):
        try:
            bus.read_byte(address)
            found.append(address)
        except OSError:
            pass

if found:
    print("Devices found:", ", ".join(hex(a) for a in found))
else:
    print("No I2C devices answered - check the wiring and pull-ups")
