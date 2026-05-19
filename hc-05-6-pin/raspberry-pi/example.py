# Raspberry Pi Python script that opens /dev/serial0 to read lines from the HC-05 and echo them back over the Bluetooth serial link.
#
# Buy this module: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-05-6pin-bluetooth-module-no-button-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install pyserial
# Disable serial console first via raspi-config

import serial
import time

bt = serial.Serial('/dev/serial0', 9600, timeout=1)
bt.reset_input_buffer()

print("HC-05 ready - pair from phone, then send text")
while True:
    if bt.in_waiting:
        line = bt.readline().decode(errors='ignore').strip()
        print(f"Got: {line}")
        bt.write(f"Echo: {line}\n".encode())
    time.sleep(0.05)
