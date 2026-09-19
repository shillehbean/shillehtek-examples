# MicroPython script that reads raw NMEA from a UART, parses GGA sentences, converts NMEA lat/lon to decimal degrees, and prints latitude, longitude and satellite count.
#
# Buy this module: https://shillehtek.com/products/gps-module-neo-m8n-antenna-battery-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gps-module-neo-m8n-antenna-battery-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import UART, Pin
import time

# GPS TXD -> GP1 (UART0 RX), GPS RXD -> GP0 (UART0 TX)
uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))

def to_degrees(raw, hemi):
    """NMEA ddmm.mmmm to decimal degrees."""
    if not raw:
        return None
    dot = raw.find(".")
    degrees = float(raw[:dot - 2])
    minutes = float(raw[dot - 2:])
    value = degrees + minutes / 60
    if hemi in ("S", "W"):
        value = -value
    return value

buf = b""
while True:
    if uart.any():
        buf += uart.read()
        while b"\n" in buf:
            line, buf = buf.split(b"\n", 1)
            text = line.decode("ascii", "ignore").strip()
            if text.startswith("$GNGGA") or text.startswith("$GPGGA"):
                p = text.split(",")
                if p[6] != "0" and p[2]:   # fix quality > 0
                    lat = to_degrees(p[2], p[3])
                    lng = to_degrees(p[4], p[5])
                    print("Lat:", lat, " Lng:", lng, " Sats:", p[7])
    time.sleep(0.05)
