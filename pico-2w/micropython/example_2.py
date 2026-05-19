# Connect the Pico 2W to a Wi‑Fi network in MicroPython, waiting up to 15 seconds and printing the assigned IP address on success.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2w-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# Raspberry Pi Pico 2W - Connect to WiFi
# Replace SSID and PASSWORD with your network credentials.

import network
import time

SSID = "your_wifi_name"
PASSWORD = "your_wifi_password"

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASSWORD)

# Wait for connection (timeout after 15 seconds)
max_wait = 15
while max_wait > 0:
    if wlan.status() < 0 or wlan.status() >= 3:
        break
    max_wait -= 1
    print("Waiting for WiFi...")
    time.sleep(1)

if wlan.status() != 3:
    raise RuntimeError("WiFi connection failed")
else:
    print("Connected!")
    print("IP address:", wlan.ifconfig()[0])
