# Raspberry Pi Python script using the adafruit-circuitpython-dht library to read temperature and humidity from a DHT22 on GPIO4, printing results every 2 seconds with basic retry error handling.
#
# Buy this module: https://shillehtek.com/products/shillehtek-dht22-with-cables
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dht22-digital-temperature-and-humidity-sensor-module-with-cable
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# DHT22 - Raspberry Pi Example
# Install: pip install adafruit-circuitpython-dht
# Also: sudo apt install libgpiod2

import time
import board
import adafruit_dht

# DATA pin connected to GPIO 4 (physical pin 7)
dht = adafruit_dht.DHT22(board.D4)

while True:
    try:
        temp = dht.temperature
        humid = dht.humidity
        print(f"Temp: {temp:.1f} C  Humidity: {humid:.1f}%")
    except RuntimeError as e:
        # Reading failed (timing issue), just retry
        print("Read error:", e.args[0])
    time.sleep(2.0)
