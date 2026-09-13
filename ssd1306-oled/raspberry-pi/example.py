# Uses the luma.oled library on a Raspberry Pi to draw static text and a live clock to the SSD1306 display over I2C.
#
# Buy this module: https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/0-96-i2c-blue-oled-display-module-4-pin-ssd1306-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 0.96" SSD1306 OLED - Raspberry Pi Example
# Install: pip install luma.oled --break-system-packages

from luma.core.interface.serial import i2c
from luma.oled.device import ssd1306
from luma.core.render import canvas
from PIL import ImageFont
import time

serial = i2c(port=1, address=0x3C)
device = ssd1306(serial, width=128, height=64)

font_big = ImageFont.load_default()

while True:
    with canvas(device) as draw:
        draw.text((0, 0),  "ShillehTek",    fill="white")
        draw.text((0, 16), "SSD1306 OLED",  fill="white")
        draw.text((0, 32), "128 x 64",      fill="white")
        draw.text((0, 48), time.strftime("%H:%M:%S"), fill="white")
    time.sleep(1)
