# Uses luma.oled on a Raspberry Pi to drive the SH1106 via I2C and render static labels plus a live HH:MM:SS clock.
#
# Buy this module: https://shillehtek.com/products/1-3-i2c-white-oled-display-module-4-pin-sh1106
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/1-3-i2c-white-oled-display-module-4-pin-sh1106-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# 1.3" SH1106 OLED - Raspberry Pi Example
# Install: pip install luma.oled --break-system-packages

from luma.core.interface.serial import i2c
from luma.oled.device import sh1106
from luma.core.render import canvas
import time

serial = i2c(port=1, address=0x3C)
device = sh1106(serial, width=128, height=64)

while True:
    with canvas(device) as draw:
        draw.text((0, 0),  "ShillehTek",    fill="white")
        draw.text((0, 16), "SH1106 OLED",   fill="white")
        draw.text((0, 32), "128 x 64",      fill="white")
        draw.text((0, 48), time.strftime("%H:%M:%S"), fill="white")
    time.sleep(1)
