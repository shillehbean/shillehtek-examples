# Uses Adafruit CircuitPython and Pillow on a Raspberry Pi to render text and a moving progress bar to the SSD1306 128x32 OLED.
#
# Buy this module: https://shillehtek.com/products/oled-ssd1306-128x32-i2c-0-91in
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/oled-ssd1306-128x32-i2c-0-91in-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 0.91" SSD1306 128x32 I2C OLED - Raspberry Pi Example
# SDA->GPIO2 (pin 3), SCL->GPIO3 (pin 5), VCC->3.3V
# Install: pip3 install adafruit-circuitpython-ssd1306 pillow

import time
import board
import busio
import adafruit_ssd1306
from PIL import Image, ImageDraw, ImageFont

i2c = busio.I2C(board.SCL, board.SDA)
oled = adafruit_ssd1306.SSD1306_I2C(128, 32, i2c, addr=0x3C)

font = ImageFont.load_default()
count = 0

try:
    while True:
        image = Image.new("1", (128, 32))
        draw = ImageDraw.Draw(image)

        draw.text((0, 0), "Raspberry Pi 128x32", font=font, fill=255)
        draw.text((0, 12), "N = {}".format(count), font=font, fill=255)
        bar = (count * 4) % 128
        draw.rectangle((0, 30, bar, 31), fill=255)

        oled.image(image)
        oled.show()
        count += 1
        time.sleep(0.2)
except KeyboardInterrupt:
    oled.fill(0)
    oled.show()
    print("Stopped by user")
