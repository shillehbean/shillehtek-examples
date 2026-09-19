# CircuitPython web server for Raspberry Pi Pico that listens on port 80 and serves a simple HTML page with hit count and uptime using the WIZNET5K driver.
#
# Buy this module: https://shillehtek.com/products/w5500-spi-ethernet-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/w5500-spi-ethernet-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# W5500 Ethernet - Pico CircuitPython web server
# Same wiring/libraries as the client example.

import time
import board, busio, digitalio
from adafruit_wiznet5k.adafruit_wiznet5k import WIZNET5K
import adafruit_wiznet5k.adafruit_wiznet5k_socketpool as socketpool

spi = busio.SPI(board.GP18, MOSI=board.GP19, MISO=board.GP16)
cs = digitalio.DigitalInOut(board.GP17)
rst = digitalio.DigitalInOut(board.GP20)

eth = WIZNET5K(spi, cs, reset=rst, is_dhcp=True)
print("Serving on http://{}".format(eth.pretty_ip(eth.ip_address)))

pool = socketpool.SocketPool(eth)
server = pool.socket()
server.bind((eth.pretty_ip(eth.ip_address), 80))
server.listen(1)

hits = 0
while True:
    conn, addr = server.accept()
    hits += 1
    conn.recv(1024)                     # discard request
    body = ("<html><body><h1>Pico + W5500</h1>"
            "<p>Hits: {} | Uptime: {:.0f} s</p>"
            "</body></html>").format(hits, time.monotonic())
    conn.send(b"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
              + body.encode())
    conn.close()
