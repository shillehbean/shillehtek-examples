# Connects the D1 Mini to Wi‑Fi and runs a minimal HTTP server that serves a simple "Hello from D1 Mini" web page.
#
# Buy this module: https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp8266-d1-mini-v3-4mb-dev-board-presoldered-manual
# More examples: https://github.com/shillehtek/examples
#

# D1 Mini V3 - join Wi-Fi and serve a hello-world page (MicroPython)
# Flash MicroPython for ESP8266 from micropython.org

import network, socket, time

SSID = "YOUR_SSID"
PASS = "YOUR_PASSWORD"

wlan = network.WLAN(network.STA_IF)
wlan.active(True)
wlan.connect(SSID, PASS)
while not wlan.isconnected():
    time.sleep(0.3)
print("IP:", wlan.ifconfig()[0])

s = socket.socket()
s.bind(("0.0.0.0", 80))
s.listen(1)

PAGE = b"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Hello from D1 Mini</h1>"

while True:
    conn, addr = s.accept()
    conn.recv(1024)
    conn.send(PAGE)
    conn.close()
