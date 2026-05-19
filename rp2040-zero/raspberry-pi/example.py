# Using CircuitPython, reads a 10k potentiometer on the ADC input GP26 and prints the raw ADC value and calculated voltage.
#
# Buy this module: https://shillehtek.com/products/rp2040-zero-microcontroller-board-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rp2040-zero-microcontroller-board-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# RP2040-Zero - read a 10k pot on GP26 (ADC0)
# Drop CircuitPython for "Waveshare RP2040-Zero" or "Raspberry Pi Pico" onto the board

import board
import analogio
import time

pot = analogio.AnalogIn(board.GP26)

while True:
    raw = pot.value                 # 0 - 65535
    voltage = raw * 3.3 / 65535
    print("Raw:", raw, "  Voltage: {:.2f} V".format(voltage))
    time.sleep(0.2)
