# Run on a MicroPython board (e.g. Raspberry Pi Pico) to read UART frames from the HLK-2410C, find footer-terminated frames, parse state and distance values, and print them over the console.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410c-human-presence-radar-motion-detection-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import UART, Pin
import time

uart = UART(0, baudrate=256000, tx=Pin(0), rx=Pin(1))
FOOTER = bytes([0xF8, 0xF7, 0xF6, 0xF5])

buf = bytearray()
print("HLK-2410C on Pico UART0")

while True:
    if uart.any():
        buf.extend(uart.read())
        while FOOTER in buf:
            end = buf.index(FOOTER) + 4
            frame = bytes(buf[:end])
            del buf[:end]
            if len(frame) >= 17:
                state = frame[8]
                move = frame[9] | (frame[10] << 8)
                static = frame[12] | (frame[13] << 8)
                print("state=%d move=%dcm static=%dcm" % (state, move, static))
    time.sleep_ms(50)
