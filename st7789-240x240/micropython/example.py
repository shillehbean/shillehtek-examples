# MicroPython example that initializes SPI and the ST7789 driver on a microcontroller, clears the screen, and draws several filled colored rectangles.
#
# Buy this module: https://shillehtek.com/products/tft-lcd-1-3-240x240-st7789-esp32-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tft-lcd-1-3-240x240-st7789-esp32-arduino-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, SPI
import st7789py as st7789   # copy st7789py.py driver to the board

spi = SPI(0, baudrate=31250000, polarity=1, phase=1,
          sck=Pin(18), mosi=Pin(19))

tft = st7789.ST7789(spi, 240, 240,
                    reset=Pin(20, Pin.OUT),
                    dc=Pin(21, Pin.OUT),
                    cs=None, rotation=0)

tft.fill(st7789.BLACK)
tft.fill_rect(20, 20, 200, 60, st7789.BLUE)
tft.fill_rect(20, 100, 200, 60, st7789.RED)
tft.fill_rect(20, 180, 200, 40, st7789.GREEN)
