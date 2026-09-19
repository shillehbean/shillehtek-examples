# Python/luma.lcd example for Raspberry Pi that draws a cyan circular outline and updates the current time every 0.5 seconds.
#
# Buy this module: https://shillehtek.com/products/round-1-28in-ips-lcd-gc9a01-240x240-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/round-1-28in-ips-lcd-gc9a01-240x240-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import time
from luma.core.interface.serial import spi
from luma.core.render import canvas
from luma.lcd.device import gc9a01

# pip3 install luma.lcd

serial = spi(port=0, device=0, gpio_DC=25, gpio_RST=27,
             bus_speed_hz=32000000)
device = gc9a01(serial, width=240, height=240, rotate=0)

while True:
    with canvas(device) as draw:
        draw.ellipse((4, 4, 236, 236), outline="cyan", width=3)
        draw.text((78, 105), time.strftime("%H:%M:%S"), fill="white")
    time.sleep(0.5)
