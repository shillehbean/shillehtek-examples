# Runs on a Raspberry Pi Pico under MicroPython to configure the ADXL345 over I2C, read 16-bit axis data, convert to signed values and m/s², and print the X/Y/Z acceleration repeatedly.
#
# Buy this module: https://shillehtek.com/products/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-adxl345-pre-soldered-3-axis-digital-angle-acceleration-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

# ADXL345 - Raspberry Pi Pico MicroPython Example
# Wiring: SDA -> GP4, SCL -> GP5, 3V3 -> 3V3 OUT, GND -> GND, CS -> 3V3

from machine import I2C, Pin
import time

ADDR = 0x53
POWER_CTL = 0x2D
DATA_FORMAT = 0x31
DATAX0 = 0x32
SCALE = 0.0039 * 9.80665  # +/-2g, full-res

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)

# Configure: full-res, +/-2g, then enable measurement mode
i2c.writeto_mem(ADDR, DATA_FORMAT, b'\x08')
i2c.writeto_mem(ADDR, POWER_CTL, b'\x08')

while True:
    raw = i2c.readfrom_mem(ADDR, DATAX0, 6)
    x = int.from_bytes(raw[0:2], 'little')
    y = int.from_bytes(raw[2:4], 'little')
    z = int.from_bytes(raw[4:6], 'little')
    # Convert unsigned to signed 16-bit
    if x > 32767: x -= 65536
    if y > 32767: y -= 65536
    if z > 32767: z -= 65536
    print("X: {:6.2f}  Y: {:6.2f}  Z: {:6.2f}  m/s^2".format(
        x * SCALE, y * SCALE, z * SCALE))
    time.sleep(0.2)
