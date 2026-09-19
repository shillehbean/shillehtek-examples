# CircuitPython client for Raspberry Pi Pico using the adafruit_wiznet5k driver to bring up Ethernet via DHCP and fetch a web page with adafruit_requests.
#
# Buy this module: https://shillehtek.com/products/w5500-spi-ethernet-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/w5500-spi-ethernet-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# W5500 Ethernet - Pico CircuitPython Example
# SCLK->GP18, MISO->GP16, MOSI->GP19, SCS->GP17, RST->GP20
# Libraries (from the Adafruit bundle, copy to /lib):
#   adafruit_wiznet5k, adafruit_requests, adafruit_connection_manager

import board
import busio
import digitalio
import adafruit_connection_manager
import adafruit_requests
from adafruit_wiznet5k.adafruit_wiznet5k import WIZNET5K

spi = busio.SPI(board.GP18, MOSI=board.GP19, MISO=board.GP16)
cs = digitalio.DigitalInOut(board.GP17)
rst = digitalio.DigitalInOut(board.GP20)

eth = WIZNET5K(spi, cs, reset=rst, is_dhcp=True)
print("IP address:", eth.pretty_ip(eth.ip_address))
print("Link up:", eth.link_status)

pool = adafruit_connection_manager.get_radio_socketpool(eth)
ssl = adafruit_connection_manager.get_radio_ssl_context(eth)
requests = adafruit_requests.Session(pool, ssl)

print("Fetching http://wifitest.adafruit.com/testwifi/index.html ...")
resp = requests.get("http://wifitest.adafruit.com/testwifi/index.html")
print("Response:", resp.text)
resp.close()
