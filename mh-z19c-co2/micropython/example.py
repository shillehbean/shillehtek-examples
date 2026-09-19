# Uses MicroPython on a Pico (UART0) to send the MH-Z19C read command, validate the checksum, and print CO2 concentration in ppm to the REPL every few seconds.
#
# Buy this module: https://shillehtek.com/products/co2-sensor-mh-z19c-ndir-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/co2-sensor-mh-z19c-ndir-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MH-Z19C CO2 Sensor - Pico MicroPython Example (raw UART protocol)
# Sensor Tx -> GP1 (UART0 RX), Sensor Rx -> GP0 (UART0 TX), Vin -> VBUS

from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1), timeout=500)

READ_CMD = bytes([0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79])

print("Warming up (about 60 s after power-on)...")

while True:
    # Clear any stale bytes, then request a reading
    while uart.any():
        uart.read()
    uart.write(READ_CMD)
    time.sleep_ms(200)

    response = uart.read(9)

    if response and len(response) == 9 and \
       response[0] == 0xFF and response[1] == 0x86:
        checksum = (0xFF - (sum(response[1:8]) & 0xFF) + 1) & 0xFF
        if checksum == response[8]:
            ppm = response[2] * 256 + response[3]
            print("CO2:", ppm, "ppm")
        else:
            print("Checksum error - reading discarded")
    else:
        print("No response - check wiring and 5V supply")

    time.sleep(5)
