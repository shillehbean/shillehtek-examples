# MicroPython script for a Raspberry Pi Pico that reads UART GGA sentences, extracts raw latitude, longitude, and satellite count, and reports when a fix is present.
#
# Buy this module: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gt-u7-gps-module-presoldered-1-manual
# More examples: https://github.com/shillehtek/examples
#

# GT-U7 GPS on Raspberry Pi Pico (MicroPython)
# Wiring: VCC->VSYS, GND->GND, GT-U7 TXD->GP1, GT-U7 RXD->GP0

from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
print("GT-U7 GPS: reading NMEA sentences...")

buffer = b""
while True:
    if uart.any():
        buffer += uart.read(uart.any())
        while b"\n" in buffer:
            line, buffer = buffer.split(b"\n", 1)
            try:
                sentence = line.decode('ascii').strip()
                if sentence.startswith('$GPGGA') or sentence.startswith('$GNGGA'):
                    parts = sentence.split(',')
                    if len(parts) > 6 and parts[6] != '0':
                        lat = parts[2]
                        lon = parts[4]
                        sats = parts[7]
                        print(f"Lat: {lat}  Lon: {lon}  Sats: {sats}")
                    else:
                        print("No fix yet...")
            except UnicodeError:
                pass
    time.sleep_ms(100)
