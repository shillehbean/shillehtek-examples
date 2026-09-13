# MicroPython example that powers the backlight, initializes SPI and the ILI9341 driver, clears the screen, and draws a text string on the display.
#
# Buy this module: https://shillehtek.com/products/Display
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-lvgl-2-8-inch-240x320-smart-display-with-resistive-touch-wifi-bluetooth-dev-board-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, SPI
import ili9341

# Backlight ON
Pin(21, Pin.OUT).value(1)

spi = SPI(1, baudrate=40000000, sck=Pin(14), mosi=Pin(13), miso=Pin(12))
display = ili9341.Display(spi, dc=Pin(2), cs=Pin(15), rst=Pin(12))

display.clear(ili9341.color565(0, 0, 0))
display.draw_text8x8(60, 100, "Hello CYD", ili9341.color565(255, 220, 0))
