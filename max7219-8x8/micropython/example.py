# Initializes SPI on a Raspberry Pi Pico with the micropython-max7219 driver to control a single MAX7219 8x8 matrix, set brightness, and display the character 'A'.
#
# Buy this module: https://shillehtek.com/products/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max7219-dot-matrix-led-display-module-8x8-driver-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# MAX7219 8x8 - Pico MicroPython
# Library: micropython-max7219 by mcauser - copy max7219.py to Pico

from machine import Pin, SPI
import max7219

spi = SPI(0, baudrate=10_000_000, polarity=0, phase=0,
          sck=Pin(2), mosi=Pin(3))
cs = Pin(5, Pin.OUT)
display = max7219.Matrix8x8(spi, cs, 1)
display.brightness(8)

display.fill(0)
display.text('A', 0, 0, 1)
display.show()
