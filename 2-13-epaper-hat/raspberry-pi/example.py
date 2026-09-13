# Python (Raspberry Pi) example using the Waveshare epd2in13_V3 driver and PIL to draw text and a rectangle on the 2.13" e-paper HAT and then put the panel to sleep.
#
# Buy this module: https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 2.13" Black & White E-Paper HAT - Raspberry Pi Example
# Uses the Waveshare epd2in13_V3 driver.
# Install: pip3 install waveshare-epaper
#   (or copy waveshare_epd/ from https://github.com/waveshareteam/e-Paper )

from waveshare_epd import epd2in13_V3
from PIL import Image, ImageDraw, ImageFont
import time

epd = epd2in13_V3.EPD()
epd.init()
epd.Clear(0xFF)  # start with a clean white screen

# Note: panel is rotated. Width/Height are the "landscape" 250x122.
image = Image.new("1", (epd.height, epd.width), 255)  # 1-bit, white
draw = ImageDraw.Draw(image)

font = ImageFont.load_default()
draw.text((10, 10), "Hello, ShillehTek!", font=font, fill=0)
draw.text((10, 40), "2.13\" E-Paper Display", font=font, fill=0)
draw.rectangle([(5, 5), (240, 80)], outline=0)

epd.display(epd.getbuffer(image))
time.sleep(2)

epd.sleep()  # very important: put the panel to sleep when done
