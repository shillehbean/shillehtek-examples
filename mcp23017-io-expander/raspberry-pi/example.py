# Uses smbus2 on a Raspberry Pi to program MCP23017 registers so port A is all outputs (blinking GPA0) and port B is inputs with pull-ups, printing when GPB0 is pressed.
#
# Buy this module: https://shillehtek.com/products/mcp23017-i2c-16bit-io-port-expander-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mcp23017-i2c-16bit-io-port-expander-presoldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# MCP23017 - Raspberry Pi Example (raw registers via smbus2)
# SDA->GPIO2, SCL->GPIO3 | Install: pip3 install smbus2

from smbus2 import SMBus
import time

ADDR   = 0x20
IODIRA = 0x00   # 1 = input, 0 = output
IODIRB = 0x01
GPPUB  = 0x0D   # port B pull-ups
GPIOA  = 0x12
GPIOB  = 0x13

bus = SMBus(1)
bus.write_byte_data(ADDR, IODIRA, 0x00)   # port A all outputs
bus.write_byte_data(ADDR, IODIRB, 0xFF)   # port B all inputs
bus.write_byte_data(ADDR, GPPUB,  0xFF)   # pull-ups on port B

print("GPA0 blinking, watching GPB0...")
try:
    led = False
    while True:
        led = not led
        bus.write_byte_data(ADDR, GPIOA, 0x01 if led else 0x00)

        b = bus.read_byte_data(ADDR, GPIOB)
        if not (b & 0x01):                # pulled low = pressed
            print("Button on GPB0 pressed!")
        time.sleep(0.25)
except KeyboardInterrupt:
    bus.write_byte_data(ADDR, GPIOA, 0x00)
    print("Stopped by user")
