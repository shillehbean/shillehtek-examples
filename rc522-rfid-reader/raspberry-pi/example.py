# Raspberry Pi Python script using the mfrc522 SimpleMFRC522 wrapper to poll for cards non-blocking and print the tag UID and stored text when a card is detected.
#
# Buy this module: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-kit-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rc522-rfid-reader-writer-module-13-56mhz-kit-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# Install: pip install mfrc522 spidev
# Enable SPI: sudo raspi-config -> Interface Options -> SPI

from mfrc522 import SimpleMFRC522
import time

reader = SimpleMFRC522()

print("Tap an RFID card...")
try:
    while True:
        id, text = reader.read_no_block()
        if id:
            print(f"UID: {id}  text: {text!r}")
            time.sleep(1)
        time.sleep(0.1)
except KeyboardInterrupt:
    pass
