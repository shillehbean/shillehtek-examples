# MicroPython example for the Pico that configures the HMC5883L via I2C, reads raw axis register data (X, Y, Z), and computes/prints a heading repeatedly.
#
# Buy this module: https://shillehtek.com/products/hmc5883l-gy-273-magnetometer-compass-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hmc5883l-gy-273-magnetometer-compass-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# HMC5883L (GY-273) Compass - Pico MicroPython Example
# SDA -> GP0, SCL -> GP1 (I2C0), VCC -> 3V3(OUT), GND -> GND
# No library needed - reads the registers directly.

from machine import Pin, I2C
import math
import time

ADDR = 0x1E   # HMC5883L (0x0D would be a QMC5883L - different chip!)

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)

if ADDR not in i2c.scan():
    raise RuntimeError("HMC5883L not found at 0x1E - check wiring "
                       "(0x0D in the scan means QMC5883L)")

# Config A: 8 samples averaged, 15 Hz  |  Config B: +/-1.3 Ga  |  Mode: continuous
i2c.writeto_mem(ADDR, 0x00, b'\x70')
i2c.writeto_mem(ADDR, 0x01, b'\x20')
i2c.writeto_mem(ADDR, 0x02, b'\x00')
time.sleep_ms(100)

def s16(hi, lo):
    v = (hi << 8) | lo
    return v - 65536 if v > 32767 else v

print("Compass ready - rotate the board slowly")

while True:
    # Data registers start at 0x03, order is X, Z, Y (big endian)
    d = i2c.readfrom_mem(ADDR, 0x03, 6)
    x = s16(d[0], d[1])
    z = s16(d[2], d[3])
    y = s16(d[4], d[5])

    heading = math.atan2(y, x)
    if heading < 0:
        heading += 2 * math.pi

    print("X:", x, " Y:", y, " Z:", z,
          " |  Heading: {:.1f} deg".format(math.degrees(heading)))
    time.sleep(0.5)
