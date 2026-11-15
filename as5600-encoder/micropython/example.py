# Use MicroPython on a Raspberry Pi Pico to read AS5600 status and the 12-bit raw angle over I2C and print angle updates repeatedly.
#
# Buy this module: https://shillehtek.com/products/as5600-magnetic-encoder-pre-soldered-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/as5600-magnetic-encoder-pre-soldered-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# AS5600 magnetic encoder on Raspberry Pi Pico (MicroPython)
# SDA = GP4 (pin 6), SCL = GP5 (pin 7), VCC = 3V3(OUT), DIR = GND
from machine import I2C, Pin
import time

AS5600_ADDR = 0x36
REG_STATUS = 0x0B       # bit 5 = magnet detected, bit 4 = too weak, bit 3 = too strong
REG_RAW_ANGLE = 0x0C    # two bytes, high byte first

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])   # expect 0x36

status = i2c.readfrom_mem(AS5600_ADDR, REG_STATUS, 1)[0]
if not status & 0x20:
    print("No magnet detected - center it over the chip")
if status & 0x10:
    print("Magnet too weak - move it closer")
if status & 0x08:
    print("Magnet too strong - move it away")

while True:
    data = i2c.readfrom_mem(AS5600_ADDR, REG_RAW_ANGLE, 2)
    raw = ((data[0] << 8) | data[1]) & 0x0FFF       # 12-bit value, 0-4095
    degrees = raw * 360 / 4096
    print("Raw:", raw, "  Angle: {:.1f} deg".format(degrees))
    time.sleep(0.1)
