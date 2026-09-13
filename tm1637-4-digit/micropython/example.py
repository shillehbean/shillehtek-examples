# MicroPython (Pico) example that sets brightness, displays two 2-digit groups (used here as 23:05), and then animates a count from 0 to 9999.
#
# Buy this module: https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-bits-tm1637-red-led-display-module-clock-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# TM1637 4-Digit Display - Pico MicroPython Example
# Copy tm1637.py from github.com/mcauser/micropython-tm1637 to the Pico first

from machine import Pin
import tm1637
import time

display = tm1637.TM1637(clk=Pin(14), dio=Pin(15))
display.brightness(4)

# Show a temperature with one decimal place
display.numbers(23, 5)    # "23:05" -- two 2-digit groups

time.sleep(2)

# Animate count 0 - 9999
for i in range(10000):
    display.number(i)
    time.sleep_ms(100)
