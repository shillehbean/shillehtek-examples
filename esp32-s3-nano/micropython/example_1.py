# Starts BLE advertising under the name 'ESP32-S3-Nano' using MicroPython so the board is discoverable by BLE apps.
#
# Buy this module: https://shillehtek.com/products/esp32-s3-nano-dev-board-presoldered-wifi-ble
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-nano-dev-board-presoldered-wifi-ble-manual
# More examples: https://github.com/shillehtek/examples
#

# ESP32-S3 Nano - Simple BLE Advertiser (MicroPython)
# Flash MicroPython for ESP32-S3 from micropython.org

import bluetooth
import time
from micropython import const

_ADV_TYPE_FLAGS = const(0x01)
_ADV_TYPE_NAME = const(0x09)

def advertising_payload(name):
    payload = bytearray()
    payload += bytes((2, _ADV_TYPE_FLAGS, 0x06))
    name_bytes = name.encode()
    payload += bytes((len(name_bytes) + 1, _ADV_TYPE_NAME)) + name_bytes
    return payload

ble = bluetooth.BLE()
ble.active(True)
ble.gap_advertise(100_000, advertising_payload("ESP32-S3-Nano"))

print("Advertising as 'ESP32-S3-Nano' - scan with any BLE app")

while True:
    time.sleep(1)
