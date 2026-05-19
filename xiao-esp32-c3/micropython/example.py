# Start BLE advertising with the device name 'XIAO-C3' using MicroPython's bluetooth module and a minimal advertising packet.
#
# Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c3-pre-soldered-with-usb-to-usb-c-cable-manual
# More examples: https://github.com/shillehtek/examples
#

# XIAO ESP32-C3 - MicroPython BLE Advertise
# Flash the official MicroPython ESP32-C3 firmware, then run this.

import bluetooth
from time import sleep

ble = bluetooth.BLE()
ble.active(True)

name = b"XIAO-C3"
adv = bytearray(b'\x02\x01\x06')              # Flags: LE general discoverable
adv += bytes([len(name) + 1, 0x09]) + name    # Complete local name

ble.gap_advertise(100_000, adv_data=adv)
print("Advertising as", name.decode())

while True:
    sleep(1)
