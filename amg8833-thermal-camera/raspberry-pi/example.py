# Runs on CircuitPython on a Raspberry Pi to read the sensor and print a coarse ASCII heatmap of the 8x8 pixels to the console in a loop.
#
# Buy this module: https://shillehtek.com/products/amg8833-ir-thermal-camera-sensor-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/amg8833-ir-thermal-camera-sensor-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
import board
import busio
import adafruit_amg88xx

# pip3 install adafruit-circuitpython-amg88xx

i2c = busio.I2C(board.SCL, board.SDA)
amg = adafruit_amg88xx.AMG88XX(i2c)   # addr=0x69

BLOCKS = " .:-=+*#%@"   # coarse ASCII heat map

while True:
    for row in amg.pixels:
        line = ""
        for t in row:
            idx = min(int((t - 18) / 2), len(BLOCKS) - 1)
            line += BLOCKS[max(idx, 0)] * 2
        print(line)
    print("-" * 16)
    time.sleep(0.3)
