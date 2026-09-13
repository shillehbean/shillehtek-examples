# Python script for a Raspberry Pi that reads LD1125H ASCII output from /dev/serial0, parses movement/occupancy frames, and prints the distance in meters.
#
# Buy this module: https://shillehtek.com/products/24GHz
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ld1125h-24ghz-mmwave-human-presence-radar-sensor-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
"""LD1125H ASCII reader for Raspberry Pi."""
import serial, re, time

PORT = "/dev/serial0"
BAUD = 115200

ser = serial.Serial(PORT, BAUD, timeout=1)
print("LD1125H Pi reader started")

pattern = re.compile(r"^(mov|occ)\s*,\s*dis\s*=\s*([0-9.]+)", re.IGNORECASE)

def handle(state, distance_m):
    label = "MOVING" if state.lower() == "mov" else "STATIC"
    print(f"{label}  {distance_m:.2f} m")

while True:
    raw = ser.readline()
    if not raw:
        continue
    try:
        text = raw.decode("ascii", errors="ignore").strip()
    except UnicodeDecodeError:
        continue
    m = pattern.match(text)
    if m:
        handle(m.group(1), float(m.group(2)))
