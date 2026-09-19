# MicroPython (Pico) example that writes MCP23017 registers directly to make GPA0 blink and monitor GPB0 with pull-ups, printing a message when the button is pressed.
#
# Buy this module: https://shillehtek.com/products/mcp23017-i2c-16bit-io-port-expander-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mcp23017-i2c-16bit-io-port-expander-presoldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MCP23017 - Pico MicroPython Example (raw registers)
# SDA->GP4, SCL->GP5

from machine import I2C, Pin
import time

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=400000)
print("I2C scan:", [hex(a) for a in i2c.scan()])   # expect 0x20

ADDR = 0x20
def reg_write(reg, val): i2c.writeto_mem(ADDR, reg, bytes([val]))
def reg_read(reg):       return i2c.readfrom_mem(ADDR, reg, 1)[0]

reg_write(0x00, 0x00)   # IODIRA: port A outputs
reg_write(0x01, 0xFF)   # IODIRB: port B inputs
reg_write(0x0D, 0xFF)   # GPPUB: pull-ups on B

print("GPA0 blinking, watching GPB0...")
led = False
while True:
    led = not led
    reg_write(0x12, 0x01 if led else 0x00)   # GPIOA

    if not (reg_read(0x13) & 0x01):          # GPIOB bit 0 low = pressed
        print("Button on GPB0 pressed!")
    time.sleep(0.25)
