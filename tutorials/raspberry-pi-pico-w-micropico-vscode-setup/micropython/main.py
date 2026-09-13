# Blinks the Pico W's onboard LED by toggling the LED pin every second.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-micropico-vscode-setup
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
from time import sleep

pin = Pin("LED", Pin.OUT)

while True:
    pin.toggle()
    sleep(1)
