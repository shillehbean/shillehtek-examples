# Implements a minimal BLE peripheral in MicroPython that advertises as 'ESP32C3-Hello' and exposes a read-only Manufacturer Name characteristic returning 'ShillehTek'.
#
# Buy this module: https://shillehtek.com/products/esp32-c3-dev-board-4mb-wifi-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c3-dev-board-4mb-wifi-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# ESP32-C3 - Minimal BLE peripheral with one read characteristic
# Discoverable as "ESP32C3-Hello"

import bluetooth
import time
from micropython import const

_FLAG_READ = const(0x0002)
_SVC_UUID  = bluetooth.UUID(0x180A)            # Device Information
_CHR_UUID  = bluetooth.UUID(0x2A29)            # Manufacturer Name

ble = bluetooth.BLE()
ble.active(True)

((handle,),) = ble.gatts_register_services(((_SVC_UUID, ((_CHR_UUID, _FLAG_READ),)),))
ble.gatts_write(handle, b"ShillehTek")

# Build advertising payload
name = b"ESP32C3-Hello"
adv = bytearray()
adv += bytes((2, 0x01, 0x06))                  # flags
adv += bytes((len(name) + 1, 0x09)) + name     # complete name

ble.gap_advertise(100_000, adv)
print("Advertising as 'ESP32C3-Hello' - connect with nRF Connect")

while True:
    time.sleep(1)
