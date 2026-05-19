# Run on MicroPython to connect the ESP32 to Wi‑Fi, print its IP address, and toggle the onboard LED every 0.5 seconds.
#
# Buy this module: https://shillehtek.com/products/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wifi-and-bluetooth-esp32-4mb-flash-uno-d1-r32-ch340g-development-board-type-b-usb-manual
# More examples: https://github.com/shillehtek/examples
#

# MicroPython on D1 R32 ESP32
# Flash latest ESP32 firmware first using esptool.py

from machine import Pin
import network, time

# Onboard LED
led = Pin(2, Pin.OUT)

# Connect to WiFi
wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect("YOUR_SSID", "YOUR_PASS")

while not wlan.isconnected():
    time.sleep(0.5)
    print("connecting...")

print("IP:", wlan.ifconfig()[0])

while True:
    led.value(not led.value())
    time.sleep(0.5)
