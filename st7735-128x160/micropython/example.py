# Uses a MicroPython ST7735 driver on a Raspberry Pi Pico (or similar) to initialize the SPI display, clear it, and draw two text lines before updating the screen.
#
# Buy this module: https://shillehtek.com/products/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-1-8-inch-tft-lcd-display-module-dual-side-soldering-manual
# More examples: https://github.com/shillehtek/examples
#

# 1.8" TFT LCD ST7735 - Pico MicroPython Example
# Requires st7735py.py and sysfont.py from GuyCarver/MicroPython_ST7735.
# Pins: SCK=GP18, MOSI=GP19, DC=GP16, RST=GP20, CS=GP17

from machine import Pin, SPI
import st7735

spi = SPI(0, baudrate=20_000_000,
          sck=Pin(18), mosi=Pin(19))

display = st7735.ST7735(
    spi,
    width=128, height=160,
    cs=Pin(17, Pin.OUT),
    dc=Pin(16, Pin.OUT),
    rst=Pin(20, Pin.OUT),
)

display.fill(st7735.color565(0, 0, 0))
display.text("ShillehTek", 8, 8, st7735.color565(255, 255, 255))
display.text("Pico ST7735", 8, 24, st7735.color565(0, 255, 0))
display.show()
