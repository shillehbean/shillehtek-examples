# MicroPython routine that reads the AMG8833 raw registers over I2C, converts the 12-bit values to Celsius, and prints the 8x8 temperature grid and maximum temperature.
#
# Buy this module: https://shillehtek.com/products/amg8833-ir-thermal-camera-sensor-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/amg8833-ir-thermal-camera-sensor-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import I2C, Pin
import time

ADDR = 0x69          # 0x68 if AD0 is tied to GND
i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)

def read_pixels():
    """64 temperatures in C, row by row (register 0x80+)."""
    data = i2c.readfrom_mem(ADDR, 0x80, 128)
    out = []
    for i in range(64):
        raw = data[2 * i] | (data[2 * i + 1] << 8)
        raw &= 0x0FFF
        if raw & 0x800:          # 12-bit two's complement
            raw -= 0x1000
        out.append(raw * 0.25)
    return out

while True:
    px = read_pixels()
    for y in range(8):
        row = px[y * 8:(y + 1) * 8]
        print(" ".join("{:5.1f}".format(t) for t in row))
    print("max: {:.1f} C".format(max(px)))
    print("-" * 47)
    time.sleep(0.5)
