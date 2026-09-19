# Uses Waveshare's epd2in9_V2 Python driver and Pillow on a Raspberry Pi to render text, a timestamp and a gauge to the 2.9" e-Paper and then put the display to sleep.
#
# Buy this module: https://shillehtek.com/products/e-ink-display-2-9-inch-296x128-spi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/e-ink-display-2-9-inch-296x128-spi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# 2.9" e-Paper - Raspberry Pi Example (Waveshare epd library)
# Setup once:
#   git clone https://github.com/waveshareteam/e-Paper
#   cd e-Paper/RaspberryPi_JetsonNano/python && sudo python3 setup.py install
#   pip3 install pillow

from waveshare_epd import epd2in9_V2
from PIL import Image, ImageDraw, ImageFont
import time

epd = epd2in9_V2.EPD()
epd.init()
epd.Clear(0xFF)

font_big = ImageFont.truetype(
    "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 28)
font_small = ImageFont.truetype(
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 16)

# landscape canvas: width=296, height=128
image = Image.new("1", (epd.height, epd.width), 255)
draw = ImageDraw.Draw(image)

draw.text((10, 8), "ShillehTek", font=font_big, fill=0)
draw.text((10, 48), "2.9 inch e-Paper on Raspberry Pi", font=font_small, fill=0)
draw.text((10, 72), time.strftime("%Y-%m-%d %H:%M"), font=font_small, fill=0)
draw.rectangle((10, 100, 286, 118), outline=0)
draw.rectangle((10, 100, 190, 118), fill=0)

epd.display(epd.getbuffer(image))
epd.sleep()          # deep sleep - image remains
print("Displayed and sleeping.")
