# CircuitPython example that reads capacitive touch on A0 and prints the touch state and raw sensor value periodically.
#
# Buy this module: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeeduino-xiao-samd21-arduino-board-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# Seeeduino XIAO SAMD21 - Capacitive touch on A0
# Drop CircuitPython for "Seeed XIAO" onto the board, then save this as code.py

import board
import touchio
import time

touch = touchio.TouchIn(board.A0)

while True:
    if touch.value:
        print("Touched! raw =", touch.raw_value)
    else:
        print("idle    raw =", touch.raw_value)
    time.sleep(0.1)
