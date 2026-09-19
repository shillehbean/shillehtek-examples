# Opens /dev/serial0 on a Raspberry Pi, reads NMEA GGA sentences with pyserial and pynmea2, and prints latitude, longitude, number of satellites and altitude.
#
# Buy this module: https://shillehtek.com/products/gps-module-neo-m8n-antenna-battery-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gps-module-neo-m8n-antenna-battery-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import serial
import pynmea2

# One-time setup:
#   sudo raspi-config > Interface Options > Serial Port
#   login shell: No / hardware serial: Yes
#   pip3 install pyserial pynmea2

port = serial.Serial("/dev/serial0", baudrate=9600, timeout=1)

while True:
    line = port.readline().decode("ascii", errors="replace").strip()
    if line.startswith("$GNGGA") or line.startswith("$GPGGA"):
        msg = pynmea2.parse(line)
        print(f"Lat: {msg.latitude:.6f}  Lng: {msg.longitude:.6f}  "
              f"Sats: {msg.num_sats}  Alt: {msg.altitude} m")
