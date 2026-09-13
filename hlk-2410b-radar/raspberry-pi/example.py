# Reads /dev/serial0 at 115200 baud on a Raspberry Pi, detects 'ON'/'OFF' lines from the HLK-2410B, and prints occupancy changes to the console.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410b-human-presence-radar-motion-detection-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import serial
import time

ser = serial.Serial('/dev/serial0', 115200, timeout=1)
present = None

print("HLK-2410B reader started. Ctrl-C to exit.")
try:
    while True:
        line = ser.readline().decode(errors='ignore').strip()
        if not line:
            continue
        now = "ON" in line
        if now != present:
            present = now
            print("Presence:", "OCCUPIED" if present else "VACANT")
        else:
            # Optional raw print for debugging
            # print("raw:", line)
            pass
except KeyboardInterrupt:
    ser.close()
