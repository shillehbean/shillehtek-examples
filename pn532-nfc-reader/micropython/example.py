# MicroPython SPI example for the Pico using an NFC_PN532 driver to read passive tag UIDs and print them to the console.
#
# Buy this module: https://shillehtek.com/products/pn532-nfc-rfid-reader-writer-module-v3
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pn532-nfc-rfid-reader-writer-module-v3-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# PN532 NFC Module V3 - Pico MicroPython Example (SPI mode)
# SCK->GP2, MOSI->GP3, MISO->GP4, SS->GP5 | S1=OFF, S2=ON
# Driver: copy NFC_PN532.py (micropython PN532 SPI driver) to the Pico
#   from https://github.com/Carglglz/NFC_PN532 (save as NFC_PN532.py)

from machine import Pin, SPI
import NFC_PN532 as nfc_mod
import time

spi = SPI(0, baudrate=1000000,
          sck=Pin(2), mosi=Pin(3), miso=Pin(4))
cs = Pin(5, Pin.OUT, value=1)

nfc = nfc_mod.PN532(spi, cs)
ic, ver, rev, support = nfc.get_firmware_version()
print("Found PN532 firmware {}.{}".format(ver, rev))

nfc.SAM_configuration()
print("Tap a card or tag...")

while True:
    uid = nfc.read_passive_target(timeout=500)
    if uid:
        print("Card UID:", ":".join("{:02X}".format(b) for b in uid))
        time.sleep(1)
    time.sleep(0.1)
