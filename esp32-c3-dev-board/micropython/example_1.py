# Uses MicroPython to scan the I2C bus on SDA=GPIO8 and SCL=GPIO9, printing any detected device addresses every two seconds.
#
# Buy this module: https://shillehtek.com/products/esp32-c3-dev-board-4mb-wifi-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c3-dev-board-4mb-wifi-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# ESP32-C3 - Scan the I2C bus for devices (MicroPython)
# Flash MicroPython for ESP32-C3 from micropython.org

from machine import I2C, Pin
import time

i2c = I2C(0, sda=Pin(8), scl=Pin(9), freq=100_000)

while True:
    devices = i2c.scan()
    if devices:
        print("Found {} I2C device(s):".format(len(devices)))
        for addr in devices:
            print("  - 0x{:02X}".format(addr))
    else:
        print("No I2C devices found")
    time.sleep(2)
