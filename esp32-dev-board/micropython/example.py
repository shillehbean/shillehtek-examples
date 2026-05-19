# Uses MicroPython to scan the I2C bus on pins 21 (SDA) and 22 (SCL) and prints detected device addresses every two seconds.
#
# Buy this module: https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-dev-board-cp2102-type-c-4mb-manual
# More examples: https://github.com/shillehtek/examples
#

# ESP-WROOM-32 - scan I2C bus for devices

from machine import I2C, Pin
import time

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100_000)

while True:
    devices = i2c.scan()
    print("Found:", [hex(d) for d in devices] if devices else "no devices")
    time.sleep(2)
