# MicroPython script for a Raspberry Pi Pico that reads LD1125H UART ASCII frames, parses mov/occ messages, and prints MOVING/STATIC with distance.
#
# Buy this module: https://shillehtek.com/products/24GHz
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ld1125h-24ghz-mmwave-human-presence-radar-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

# LD1125H on Raspberry Pi Pico (MicroPython)
from machine import UART, Pin
import time

uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))
buf = ""

print("LD1125H Pico reader ready")

while True:
    if uart.any():
        chunk = uart.read(uart.any())
        try:
            buf += chunk.decode("ascii")
        except UnicodeError:
            buf = ""
            continue
        while "\n" in buf:
            line, buf = buf.split("\n", 1)
            line = line.strip()
            if not line:
                continue
            if line.startswith("mov") or line.startswith("occ"):
                label = "MOVING" if line.startswith("mov") else "STATIC"
                eq = line.find("=")
                if eq > 0:
                    try:
                        d = float(line[eq + 1:])
                        print(label, "%.2f m" % d)
                    except ValueError:
                        pass
    time.sleep_ms(20)
