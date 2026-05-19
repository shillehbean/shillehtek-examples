# Use Python with smbus2 on a Raspberry Pi to read a byte from a 5V I2C device through the TXS0108E level shifter (with OE and pull-ups configured).
#
# Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-txs0108e-high-speed-full-duplex-8-channel-logic-level-bi-directional-converter-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# TXS0108E - Reading a 5V I2C device from a Raspberry Pi
# Pi SDA (GPIO 2) -> A1, Pi SCL (GPIO 3) -> A2
# B1, B2 -> 5V device SDA/SCL with 4.7k pull-ups to 5V
# VA = 3.3V (Pin 1), VB = 5V (Pin 2), OE = 3.3V

from smbus2 import SMBus
import time

I2C_BUS = 1
DEVICE_ADDR = 0x48  # example: PCF8591 5V ADC

with SMBus(I2C_BUS) as bus:
    while True:
        try:
            # Read one byte from the 5V device
            value = bus.read_byte(DEVICE_ADDR)
            print("Read from 0x{:02X}: {}".format(DEVICE_ADDR, value))
        except OSError as e:
            print("I2C error - check pull-ups and OE pin:", e)
        time.sleep(1)
