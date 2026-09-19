# Raspberry Pi example using the st7789 Python library and Pillow to draw a bordered rectangle and the text 'Hello from Pi!' then display the image on the 240x240 panel.
#
# Buy this module: https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tft-lcd-1-3-240x240-st7789-esp32-arduino-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import st7789
from PIL import Image, ImageDraw, ImageFont

# pip3 install st7789 pillow

disp = st7789.ST7789(
    port=0, cs=0, dc=24, rst=25, backlight=18,
    width=240, height=240, rotation=0, spi_speed_hz=40000000)

img = Image.new("RGB", (240, 240), (0, 0, 30))
draw = ImageDraw.Draw(img)
draw.rectangle((10, 10, 230, 230), outline=(0, 200, 255), width=4)
font = ImageFont.load_default()
draw.text((60, 110), "Hello from Pi!", fill=(255, 255, 0), font=font)

disp.display(img)
input("Showing - press Enter to quit")
