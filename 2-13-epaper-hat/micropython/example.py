# MicroPython example for the Raspberry Pi Pico using Waveshare's Pico_ePaper driver to draw text and shapes into the display buffer, update the e-paper, and then sleep the module.
#
# Buy this module: https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 2.13" Black & White E-Paper - Pico MicroPython Example
# Driver: copy Pico_ePaper-2.13.py from Waveshare's GitHub
#   ( https://github.com/waveshareteam/Pico_ePaper_Code )
# Save as Pico_ePaper.py on the Pico, then:

from machine import Pin, SPI
import framebuf
import time

# Driver wires CS=9, DC=8, RST=12, BUSY=13, SCK=10, MOSI=11
from Pico_ePaper import EPD_2in13

epd = EPD_2in13()
epd.Clear(0xff)

# Width/Height come from the driver
epd.fill(0xff)
epd.text("Hello, ShillehTek!", 5, 10, 0x00)
epd.text("2.13\" E-Paper", 5, 30, 0x00)
epd.text("Pico + MicroPython", 5, 50, 0x00)
epd.rect(0, 0, epd.width, epd.height, 0x00)

epd.display(epd.buffer)
time.sleep(2)

epd.sleep()
