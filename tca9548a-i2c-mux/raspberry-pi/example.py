# Uses smbus2 on a Raspberry Pi to select each TCA9548A channel and scan for connected I2C devices, listing found addresses.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cjmcu-9548-tca9548a-1-to-8-i2c-8-channel-multiplexer-module-manual
# More examples: https://github.com/shillehtek/examples
#

from smbus2 import SMBus
import time

TCA_ADDR = 0x70
BUS = 1

def tca_select(bus, channel):
    if channel > 7: return
    bus.write_byte(TCA_ADDR, 1 << channel)

with SMBus(BUS) as bus:
    for ch in range(8):
        tca_select(bus, ch)
        time.sleep(0.05)
        print(f"Channel {ch}:")
        for addr in range(0x03, 0x78):
            if addr == TCA_ADDR:
                continue
            try:
                bus.read_byte(addr)
                print(f"  Found 0x{addr:02X}")
            except OSError:
                pass
