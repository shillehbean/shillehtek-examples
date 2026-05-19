# Toggles the onboard user LED in a loop using MicroPython's pyb LED and delay functions (for use with the STM32F411 MicroPython firmware).
#
# Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-authentic-stm32f411ceu6
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-authentic-stm32f411ceu6-manual
# More examples: https://github.com/shillehtek/examples
#

# STM32F411 Black Pill - MicroPython Hello World
# Flash the official MicroPython STM32F411 firmware first.
# Then connect via USB serial and run this script.

from pyb import LED, Pin, delay

led = LED(1)  # PC13 user LED maps to LED(1) on most ports

while True:
    led.toggle()
    delay(250)
