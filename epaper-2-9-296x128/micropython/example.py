# Demonstrates the MicroPython driver for the 2.9" e-Paper on a Pico: draw text and rectangles to the driver's framebuf, display the buffer, then enter sleep so the image persists.
#
# Buy this module: https://shillehtek.com/products/e-ink-display-2-9-inch-296x128-spi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/e-ink-display-2-9-inch-296x128-spi-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 2.9" e-Paper - Pico MicroPython Example
# Driver: copy Pico_ePaper-2.9.py from Waveshare's Pico_ePaper_Code repo
#   to the Pico as epaper29.py (it contains class EPD_2in9)
# Wiring here matches the tab: CS=9, DC=8, RST=12, BUSY=13, SCK=10, MOSI=11

from epaper29 import EPD_2in9
import time

epd = EPD_2in9()          # driver sets up SPI1 + pins
epd.Clear(0xff)

# The driver exposes a framebuf: draw with standard framebuf calls
epd.fill(0xff)
epd.text("ShillehTek", 8, 8, 0x00)
epd.text("e-Paper on Pico", 8, 24, 0x00)
epd.text("No power needed", 8, 40, 0x00)
epd.text("to keep this text!", 8, 56, 0x00)
epd.rect(8, 76, 120, 12, 0x00)
epd.fill_rect(8, 76, 80, 12, 0x00)

epd.display(epd.buffer)
time.sleep(2)
epd.sleep()               # image persists with zero power
print("Displayed and sleeping.")
