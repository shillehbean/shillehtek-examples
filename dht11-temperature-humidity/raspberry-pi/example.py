# Reads temperature and humidity from a DHT11 connected to GPIO4 using Adafruit's CircuitPython DHT library and prints readings every 2 seconds with basic error handling.
#
# Buy this module: https://shillehtek.com/products/shillehtek-dht11-with-cables
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/f
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# DHT11 - Raspberry Pi Python Example
# Install: sudo pip3 install adafruit-circuitpython-dht
# Also need: sudo apt install libgpiod2

import time
import board
import adafruit_dht

dht = adafruit_dht.DHT11(board.D4)

while True:
    try:
        t = dht.temperature
        h = dht.humidity
        print(f"Temp: {t} C  Humidity: {h}%")
    except RuntimeError as e:
        print(f"Read error: {e}")
    time.sleep(2)
