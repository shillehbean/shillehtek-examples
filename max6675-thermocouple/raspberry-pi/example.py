# Uses Python with spidev on a Raspberry Pi to read the MAX6675 over SPI, convert the raw data to Celsius, and print temperature or a disconnected warning in a loop.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max6675-module-k-type-thermocouple-sensor-measures-up-to-1024-degrees-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MAX6675 K-type thermocouple - Raspberry Pi
# Uses kernel SPI via spidev. Enable SPI in raspi-config first.
# pip install spidev

import spidev
import time

spi = spidev.SpiDev()
spi.open(0, 0)            # bus 0, CE0
spi.max_speed_hz = 1000000
spi.mode = 0

def read_temp_c():
    raw = spi.xfer2([0x00, 0x00])
    value = (raw[0] << 8) | raw[1]

    # Bit 2 = open-thermocouple flag
    if value & 0x4:
        return None

    # Bits 14:3 hold the 12-bit temperature, 0.25 C per step
    temp = (value >> 3) * 0.25
    return temp

try:
    while True:
        c = read_temp_c()
        if c is None:
            print("Thermocouple disconnected!")
        else:
            print(f"Temp: {c:.2f} C")
        time.sleep(0.3)
except KeyboardInterrupt:
    spi.close()
