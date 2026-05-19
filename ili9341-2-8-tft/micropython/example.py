# MicroPython example that sets up the ILI9341 over SPI (e.g., on a Pico), clears the display, writes text, and draws a rectangle using the rdagger driver.
#
# Buy this module: https://shillehtek.com/products/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/2-8-spi-tft-lcd-touch-screen-module-240x320-ili9341-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# Install "rdagger/micropython-ili9341" driver to /lib

from ili9341 import Display, color565
from machine import Pin, SPI

spi = SPI(0, baudrate=40000000, sck=Pin(18), mosi=Pin(19))
display = Display(spi, dc=Pin(21), cs=Pin(17), rst=Pin(20))

display.clear(color565(0, 0, 0))
display.draw_text8x8(20, 20, "Hello Pico!", color565(255, 255, 255))
display.draw_rectangle(20, 60, 200, 40, color565(0, 255, 255))
