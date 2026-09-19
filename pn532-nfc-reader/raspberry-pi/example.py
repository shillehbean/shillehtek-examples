# CircuitPython I2C example for Raspberry Pi that polls for passive NFC tags and prints each card's UID when detected.
#
# Buy this module: https://shillehtek.com/products/pn532-nfc-rfid-reader-writer-module-v3
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pn532-nfc-rfid-reader-writer-module-v3-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# PN532 NFC Module V3 - Raspberry Pi Example (I2C mode)
# SDA->GPIO2, SCL->GPIO3, VCC->3.3V | S1=ON, S2=OFF
# Install: pip3 install adafruit-circuitpython-pn532

import time
import board
import busio
from adafruit_pn532.i2c import PN532_I2C

i2c = busio.I2C(board.SCL, board.SDA)
pn532 = PN532_I2C(i2c, debug=False)

ic, ver, rev, support = pn532.firmware_version
print("Found PN532 firmware {}.{}".format(ver, rev))

pn532.SAM_configuration()
print("Tap a card or tag...")

seen = None
try:
    while True:
        uid = pn532.read_passive_target(timeout=0.5)
        if uid is not None:
            uid_str = ":".join("{:02X}".format(b) for b in uid)
            if uid_str != seen:
                print("Card UID:", uid_str)
                seen = uid_str
        else:
            seen = None
        time.sleep(0.1)
except KeyboardInterrupt:
    print("Stopped by user")
