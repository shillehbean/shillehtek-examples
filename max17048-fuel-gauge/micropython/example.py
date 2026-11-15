# Run on a MicroPython board (e.g., Raspberry Pi Pico) to read the MAX17048 VCELL and SOC registers via I2C and print voltage and percentage repeatedly.
#
# Buy this module: https://shillehtek.com/products/max17048-i2c-single-cell-fuel-gauge-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max17048-i2c-single-cell-fuel-gauge-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MAX17048 battery fuel gauge on Raspberry Pi Pico (MicroPython)
# Wiring: VIN = 3V3(OUT), GND = GND, SDA = GP4, SCL = GP5
# A battery must be plugged into the board, or the chip will not answer.
from machine import I2C, Pin
import time

ADDR = 0x36
REG_VCELL = 0x02      # cell voltage, 78.125 uV per count
REG_SOC = 0x04        # state of charge, 1/256 % per count

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=100000)


def read_register(reg):
    data = i2c.readfrom_mem(ADDR, reg, 2)
    return (data[0] << 8) | data[1]


while True:
    try:
        volts = read_register(REG_VCELL) * 78.125 / 1000000
        percent = read_register(REG_SOC) / 256
        print("Battery: {:.3f} V  {:.1f} %".format(volts, percent))
    except OSError:
        print("MAX17048 not found - is a battery connected?")
    time.sleep(2)
