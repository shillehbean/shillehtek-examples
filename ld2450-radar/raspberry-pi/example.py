# Python script for Raspberry Pi that opens the serial port at 256000 baud, locates 30-byte frames from the HLK-LD2450, decodes signed x/y/speed values and distance, and prints any detected targets.
#
# Buy this module: https://shillehtek.com/products/24GHz
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-ld2450-24ghz-mmwave-radar-human-body-tracking-sensor-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
"""HLK-LD2450 reader for Raspberry Pi - prints up to 3 tracked targets."""
import serial, time

PORT = "/dev/serial0"
BAUD = 256000

HEADER = b"\xAA\xFF\x03\x00"
FOOTER = b"\x55\xCC"
FRAME_LEN = 30

def decode_signed(lo, hi):
    v = ((hi << 8) | lo) & 0x7FFF
    return v if (hi & 0x80) else -v

ser = serial.Serial(PORT, BAUD, timeout=0.5)
print("LD2450 Pi reader started")

buf = bytearray()
while True:
    buf += ser.read(64)
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
            x   = decode_signed(frame[o + 0], frame[o + 1])
            y   = decode_signed(frame[o + 2], frame[o + 3])
            spd = decode_signed(frame[o + 4], frame[o + 5])
            dist = frame[o + 6] | (frame[o + 7] << 8)
            if x or y or dist:
                print(f"T{t + 1}  x={x:5} mm  y={y:5} mm  "
                      f"spd={spd:4} cm/s  dist={dist}")
        buf = buf[i + FRAME_LEN:]
    time.sleep(0.02)
