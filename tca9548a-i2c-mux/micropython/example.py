# In MicroPython, iterates through the TCA9548A channels, scans the active I2C bus on each channel, and prints the addresses of detected devices.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-9548-tca9548a-1-to-8-i2c-8-channel-multiplexer-module-manual
# More examples: https://github.com/shillehtek/examples
#

from machine import Pin, I2C
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)
TCA_ADDR = 0x70

def tca_select(channel):
    if 0 <= channel <= 7:
        i2c.writeto(TCA_ADDR, bytes([1 << channel]))

for ch in range(8):
    tca_select(ch)
    time.sleep_ms(50)
    devs = i2c.scan()
    print(f"Channel {ch}: {[hex(d) for d in devs if d != TCA_ADDR]}")
