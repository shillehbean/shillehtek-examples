# Uses MicroPython's network API to enable the station interface and scan nearby Wi‑Fi networks, printing SSID, channel and RSSI for each.
#
# Buy this module: https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable-manual
# More examples: https://github.com/shillehtek/examples
#

# XIAO ESP32-C6 - MicroPython Wi-Fi Scan
# Requires the official MicroPython ESP32-C6 firmware.

import network
import time

wlan = network.WLAN(network.STA_IF)
wlan.active(True)

print("Scanning Wi-Fi...")
networks = wlan.scan()
for ssid, bssid, channel, rssi, security, hidden in networks:
    print("{:32}  ch{:2}  {:4} dBm".format(ssid.decode(), channel, rssi))
