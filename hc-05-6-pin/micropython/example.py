# MicroPython UART echo for Pico: reads lines from the HC-05 on UART0 (pins 0/1), prints them to the REPL, and sends an "Echo:" response back.
#
# Buy this module: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-05-6pin-bluetooth-module-no-button-manual
# More examples: https://github.com/shillehtek/examples
#

# HC-05 on Pico - MicroPython Echo Example
from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
print("HC-05 ready")

while True:
    if uart.any():
        data = uart.readline()
        if data:
            text = data.decode().strip()
            print("Got:", text)
            uart.write("Echo: " + text + "\n")
    time.sleep_ms(50)
