# Raspberry Pi Python logger that listens on /dev/serial0 for HC-12 packets, prints each line with a timestamp, and appends entries to hc12_log.csv.
#
# Buy this module: https://shillehtek.com/products/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# HC-12 - Raspberry Pi receiver/logger
# TXD->GPIO15, RXD->GPIO14 | Install: pip3 install pyserial

import serial, time

port = serial.Serial("/dev/serial0", 9600, timeout=1)
print("Listening for HC-12 packets... Ctrl+C to stop")

try:
    with open("hc12_log.csv", "a") as log:
        while True:
            line = port.readline().decode(errors="ignore").strip()
            if line:
                stamp = time.strftime("%Y-%m-%d %H:%M:%S")
                print(f"[{stamp}] {line}")
                log.write(f"{stamp},{line}\n")
                log.flush()
except KeyboardInterrupt:
    print("Stopped by user")
