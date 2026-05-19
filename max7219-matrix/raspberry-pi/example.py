# Uses the luma.led_matrix library on a Raspberry Pi to scroll "ShillehTek MAX7219" across four cascaded MAX7219 displays over SPI.
#
# Buy this module: https://shillehtek.com/products/max7219-4-in-1-dot-matrix-display-module-red
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max7219-4-in-1-dot-matrix-display-module-red-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# MAX7219 4-in-1 Dot Matrix - Raspberry Pi Scrolling Text
# Install: pip install luma.led_matrix --break-system-packages

from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.core.legacy import text, show_message
from luma.core.legacy.font import proportional, CP437_FONT
from luma.led_matrix.device import max7219
import time

serial = spi(port=0, device=0, gpio=noop())
device = max7219(serial, cascaded=4, block_orientation=-90, rotate=0)
device.contrast(0x30)   # 0x00 - 0xFF

show_message(device, "ShillehTek MAX7219",
             fill="white", font=proportional(CP437_FONT),
             scroll_delay=0.04)
