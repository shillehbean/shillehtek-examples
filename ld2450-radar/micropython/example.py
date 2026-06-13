# MicroPython example for Raspberry Pi Pico that reads the HLK-LD2450 over UART0 at 256000 baud, finds complete frames, decodes up to three targets, and prints their x/y, speed, and distance.
#
# Buy this module: https://shillehtek.com/products/24GHz
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-ld2450-24ghz-mmwave-radar-human-body-tracking-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

# HLK-LD2450 on Raspberry Pi Pico (MicroPython)
from machine import UART, Pin
import time

uart = UART(0, baudrate=256000, tx=Pin(0), rx=Pin(1))
buf = bytearray()
HEADER = b"\xAA\xFF\x03\x00"
FOOTER = b"\x55\xCC"
FRAME_LEN = 30

def decode_signed(lo, hi):
    v = ((hi << 8) | lo) & 0x7FFF
    return v if (hi & 0x80) else -v

print("LD2450 Pico reader ready")

while True:
    if uart.any():
        buf += uart.read(uart.any())
    while True:
        i = buf.find(HEADER)
        if i < 0 or len(buf) - i < FRAME_LEN:
            break
        frame = buf[i:i + FRAME_LEN]
        if frame[-2:] != FOOTER:
            buf = buf[i + 1:]
            continue
        for t in range(3):
            o = 4 + t * 8
            x   = decode_signed(frame[o], frame[o + 1])
            y   = decode_signed(frame[o + 2], frame[o + 3])
            spd = decode_signed(frame[o + 4], frame[o + 5])
            dist = frame[o + 6] | (frame[o + 7] << 8)
            if x or y or dist:
                print("T%d x=%d y=%d spd=%d dist=%d" % (t + 1, x, y, spd, dist))
        buf = buf[i + FRAME_LEN:]
    time.sleep_ms(20)
