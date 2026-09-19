# Performs a WiFi scan under MicroPython (printing SSID, channel and RSSI) and provides a small connect(ssid, password) helper that waits for association.
#
# Buy this module: https://shillehtek.com/products/esp32-wrover-4mb-psram-wifi-bluetooth-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-wrover-4mb-psram-wifi-bluetooth-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ESP32-WROVER - MicroPython WiFi scan
import network
import time

sta = network.WLAN(network.STA_IF)
sta.active(True)

print("Scanning...")
for ssid, bssid, ch, rssi, sec, hidden in sta.scan():
    print("{:24s} ch{:2d} {:4d} dBm".format(ssid.decode(), ch, rssi))

# Simple connect helper
def connect(ssid, password, timeout=15):
    sta.connect(ssid, password)
    t0 = time.time()
    while not sta.isconnected():
        if time.time() - t0 > timeout:
            raise RuntimeError("WiFi connect timeout")
        time.sleep(0.5)
    print("Connected:", sta.ifconfig()[0])

# connect("YOUR_WIFI", "YOUR_PASSWORD")
