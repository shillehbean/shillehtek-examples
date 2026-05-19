# Runs on a Raspberry Pi, reads NMEA sentences from /dev/serial0 using pyserial and pynmea2, and prints position, speed, and UTC time when an RMC sentence reports a valid fix.
#
# Buy this module: https://shillehtek.com/products/gt-u7-gps-module-presoldered-1
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gt-u7-gps-module-presoldered-1-manual
# More examples: https://github.com/shillehtek/examples
#

# GT-U7 GPS on Raspberry Pi
# Install: pip install pyserial pynmea2 --break-system-packages
# Enable serial hardware first: sudo raspi-config

import serial
import pynmea2

ser = serial.Serial('/dev/serial0', 9600, timeout=1)
print("GT-U7 GPS: reading NMEA from /dev/serial0")

while True:
    try:
        line = ser.readline().decode('ascii', errors='replace').strip()
        if line.startswith('$GPRMC') or line.startswith('$GNRMC'):
            msg = pynmea2.parse(line)
            if msg.status == 'A':  # 'A' = valid fix
                print(f"Lat: {msg.latitude:.6f}  Lon: {msg.longitude:.6f}  "
                      f"Speed: {msg.spd_over_grnd} knots  UTC: {msg.timestamp}")
            else:
                print("Waiting for GPS fix...")
    except pynmea2.ParseError:
        continue
    except KeyboardInterrupt:
        break

ser.close()
