# Performs an I2C device scan on a MicroPython board (e.g., Raspberry Pi Pico) using specified SDA/SCL pins through the level shifter and prints found addresses.
#
# Buy this module: https://shillehtek.com/products/shillehtek-iic-i2c-logic-level-converter-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/iic-i2c-logic-level-converter-pre-soldered-bi-directional
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Pico I2C scan through the level shifter (GP0 SDA, GP1 SCL)

from machine import I2C, Pin

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=100000)
devices = i2c.scan()
print("Devices found (through shifter):", [hex(d) for d in devices])
