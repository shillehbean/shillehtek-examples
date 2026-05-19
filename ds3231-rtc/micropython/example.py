# Minimal MicroPython example for Pico/RP2040 that reads the DS3231 time registers over I2C, converts BCD values to integers, and prints the timestamp once per second.
#
# Buy this module: https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery-manual
# More examples: https://github.com/shillehtek/examples
#

# DS3231 on Pico - MicroPython
# Save ds3231_micropython.py from the micropython-stubs repo, or use this minimal driver

from machine import I2C, Pin
import time

I2C_ADDR = 0x68
i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)

def bcd2dec(b):
    return (b // 16) * 10 + (b % 16)
def dec2bcd(d):
    return (d // 10) * 16 + (d % 10)

def get_time():
    data = i2c.readfrom_mem(I2C_ADDR, 0x00, 7)
    sec = bcd2dec(data[0] & 0x7F)
    minute = bcd2dec(data[1])
    hour = bcd2dec(data[2] & 0x3F)
    day = bcd2dec(data[4])
    month = bcd2dec(data[5] & 0x1F)
    year = 2000 + bcd2dec(data[6])
    return (year, month, day, hour, minute, sec)

while True:
    print(get_time())
    time.sleep(1)
