# MicroPython example for Raspberry Pi Pico that polls a PIR input on Pin 15, toggles the onboard LED on motion, and prints events after a 30s warm-up.
#
# Buy this module: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr501-pir-motion-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# HC-SR501 PIR on Raspberry Pi Pico

from machine import Pin
import time

pir = Pin(15, Pin.IN)
led = Pin(25, Pin.OUT)  # onboard LED

print("Warming up PIR sensor...")
time.sleep(30)
print("Ready.")

while True:
    if pir.value() == 1:
        led.on()
        print("Motion detected!")
    else:
        led.off()
    time.sleep_ms(100)
