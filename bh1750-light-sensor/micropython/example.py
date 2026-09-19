# Reads BH1750 on a Raspberry Pi Pico (MicroPython) over I2C0, converts sensor data to lux, and prints to the REPL every second.
#
# Buy this module: https://shillehtek.com/products/shillehtek-gy-302-bh1750-pre-soldered-light-intensity-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/bh1750-pre-soldered-light-intensity-module
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# BH1750 on Pico via I2C0 (GP0 SDA, GP1 SCL)

from machine import I2C, Pin
import time

BH1750_ADDR = 0x23
CONT_H_RES  = 0x10

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=100000)
print("I2C scan:", [hex(d) for d in i2c.scan()])

i2c.writeto(BH1750_ADDR, bytes([CONT_H_RES]))
time.sleep_ms(200)

while True:
    data = i2c.readfrom(BH1750_ADDR, 2)
    raw  = (data[0] << 8) | data[1]
    lux  = raw / 1.2
    print("Light: {:.1f} lx".format(lux))
    time.sleep(1)
