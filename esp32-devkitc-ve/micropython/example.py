# Runs on MicroPython to scan the I2C bus (SDA=21, SCL=22) repeatedly and prints any detected device addresses.
#
# Buy this module: https://shillehtek.com/products/esp32-devkitc-ve-8mb-flash-8mb-psram-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-devkitc-ve-8mb-flash-8mb-psram-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# ESP32-DevKitC-VE - scan I2C bus for devices (MicroPython)
# Flash MicroPython for ESP32-WROVER from micropython.org

from machine import I2C, Pin
import time

i2c = I2C(0, sda=Pin(21), scl=Pin(22), freq=100_000)

while True:
    devices = i2c.scan()
    if devices:
        print("Found:", [hex(d) for d in devices])
    else:
        print("No I2C devices")
    time.sleep(2)
