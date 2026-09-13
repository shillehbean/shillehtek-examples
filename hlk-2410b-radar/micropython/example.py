# MicroPython script for a Pico/RP2040 using UART0 to read HLK-2410B messages and print presence state transitions to the REPL.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hlk-2410b-human-presence-radar-motion-detection-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import UART, Pin
import time

uart = UART(0, baudrate=115200, tx=Pin(0), rx=Pin(1))
buf = ""
present = None

print("HLK-2410B on Pico UART0")

while True:
    if uart.any():
        chunk = uart.read()
        if chunk:
            buf += chunk.decode('utf-8', 'ignore')
            while '\n' in buf or '\r' in buf:
                # split on either line ending
                idx = min([i for i in (buf.find('\n'), buf.find('\r')) if i >= 0])
                line, buf = buf[:idx].strip(), buf[idx+1:]
                if line:
                    now = ("ON" in line)
                    if now != present:
                        present = now
                        print("Presence:", "OCCUPIED" if present else "VACANT")
    time.sleep_ms(50)
