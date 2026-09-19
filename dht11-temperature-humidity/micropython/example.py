# Uses MicroPython's built-in dht module to measure temperature and humidity on Pin 15 (e.g., Raspberry Pi Pico) and prints the readings every 2 seconds with basic error handling.
#
# Buy this module: https://shillehtek.com/products/shillehtek-dht11-with-cables
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/f
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# DHT11 - Pico MicroPython
# Built-in dht module — no library install needed.

from machine import Pin
import dht
import time

sensor = dht.DHT11(Pin(15))

while True:
    try:
        sensor.measure()
        t = sensor.temperature()
        h = sensor.humidity()
        print("Temp: {} C  Humidity: {}%".format(t, h))
    except OSError as e:
        print("Read error:", e)
    time.sleep(2)
