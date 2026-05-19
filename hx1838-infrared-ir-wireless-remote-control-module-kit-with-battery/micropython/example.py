# Runs a MicroPython NEC protocol receiver on a Pico (or similar) that invokes a callback to print received NEC-format IR codes and addresses.
#
# Buy this module: https://shillehtek.com/products/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hx1838-infrared-ir-wireless-remote-control-module-kit-with-battery-manual
# More examples: https://github.com/shillehtek/examples
#

# IR receiver on Pico - MicroPython
# Use the micropython-ir library by peterhinch
# https://github.com/peterhinch/micropython_ir

from machine import Pin
from ir_rx.nec import NEC_8

def callback(data, addr, ctrl):
    if data > 0:
        print('Code: 0x{:02X}  Addr: 0x{:04X}'.format(data, addr))

ir = NEC_8(Pin(15, Pin.IN), callback)
print("Press buttons...")
while True:
    pass
