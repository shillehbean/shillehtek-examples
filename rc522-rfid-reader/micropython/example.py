# MicroPython example for RP2040 (Pico) that polls for RC522 tags using the micropython-mfrc522 library and prints the tag UID in hex when found.
#
# Buy this module: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-kit-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rc522-rfid-reader-writer-module-13-56mhz-kit-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# RC522 on Pico - MicroPython
# Use the micropython-mfrc522 library by danjperron
# https://github.com/danjperron/micropython-mfrc522

from mfrc522 import MFRC522
import utime

reader = MFRC522(spi_id=0, sck=18, mosi=19, miso=16, cs=17, rst=20)

print("Tap an RFID card...")
while True:
    (stat, tag_type) = reader.request(reader.REQIDL)
    if stat == reader.OK:
        (stat, uid) = reader.SelectTagSN()
        if stat == reader.OK:
            print('UID:', '-'.join(['{:02X}'.format(x) for x in uid]))
            utime.sleep(1)
    utime.sleep_ms(100)
