# Poll the MAX17048 from a Raspberry Pi using smbus2 to display the battery voltage and state-of-charge in the terminal.
#
# Buy this module: https://shillehtek.com/products/max17048-i2c-single-cell-fuel-gauge-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max17048-i2c-single-cell-fuel-gauge-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MAX17048 battery fuel gauge on Raspberry Pi - read cell voltage and state of charge
# Enable I2C (sudo raspi-config), then install the library: sudo apt install python3-smbus2
# Wiring: VIN = 3V3 (pin 1), GND = pin 6, SDA = GPIO 2 (pin 3), SCL = GPIO 3 (pin 5)
# A battery must be plugged into the board, or the chip will not answer.
import time
from smbus2 import SMBus

ADDR = 0x36
REG_VCELL = 0x02      # cell voltage, 78.125 uV per count
REG_SOC = 0x04        # state of charge, 1/256 % per count


def read_register(bus, reg):
    high, low = bus.read_i2c_block_data(ADDR, reg, 2)
    return (high << 8) | low


with SMBus(1) as bus:
    while True:
        try:
            volts = read_register(bus, REG_VCELL) * 78.125 / 1000000
            percent = read_register(bus, REG_SOC) / 256
            print(f"Battery: {volts:.3f} V  {percent:.1f} %")
        except OSError:
            print("MAX17048 not found - is a battery connected?")
        time.sleep(2)
