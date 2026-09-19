# MicroPython example for boards like the Raspberry Pi Pico that uses the built-in dht module to measure temperature and humidity from a DHT22 on Pin 15 and print readings every 2 seconds.
#
# Buy this module: https://shillehtek.com/products/shillehtek-dht22-with-cables
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/dht22-digital-temperature-and-humidity-sensor-module-with-cable
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# DHT22 - Pico MicroPython Example
# Uses built-in dht module (no install needed)

from machine import Pin
import dht
import time

sensor = dht.DHT22(Pin(15))

while True:
    try:
        sensor.measure()
        t = sensor.temperature()
        h = sensor.humidity()
        print("Temp: {:.1f} C  Humidity: {:.1f}%".format(t, h))
    except OSError as e:
        print("Failed to read sensor:", e)
    time.sleep(2)
