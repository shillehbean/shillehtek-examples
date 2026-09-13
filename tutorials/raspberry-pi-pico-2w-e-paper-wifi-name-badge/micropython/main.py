# MicroPython script for the Pico W that initializes the 2.13" e-paper HAT, draws header, message, and footer text for a name badge, updates the display, and puts the display to sleep to save power.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-2w-e-paper-wifi-name-badge
# Parts used: https://shillehtek.com/products/2-13-inch-black-white-e-paper-hat-ink-screen-spi-250x122-for-raspberry-pi
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
#             https://shillehtek.com/products/tp4056-1a-lipo-battery-charging-board-type-c-with-current-protection
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, SPI
import framebuf
from epaper2in13_v3 import EPD_2in13

spi = SPI(1, baudrate=4000000,
          sck=Pin(10), mosi=Pin(11))
epd = EPD_2in13(spi, cs=9, dc=8, rst=12, busy=13)

epd.init()
epd.fill(0xFF)  # white

# Header
epd.text("MAHMOOD SHILLEH", 8, 8, 0)
epd.text("Founder, ShillehTek", 8, 24, 0)

# Big call-out line
epd.text("Ask me about", 8, 56, 0)
epd.text("mmWave radar!", 8, 72, 0)

# Footer
epd.text("shillehtek.com", 8, 105, 0)

epd.display()
epd.sleep()
