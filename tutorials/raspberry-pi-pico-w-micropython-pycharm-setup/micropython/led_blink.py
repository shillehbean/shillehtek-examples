# Toggles the Raspberry Pi Pico W onboard LED in a loop with a 0.1 second delay between state changes.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-micropython-pycharm-setup
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import machine
import time

led_pin = machine.Pin("LED", machine.Pin.OUT)  # GPIO pin 25 controls the onboard LED

while True:
    led_pin.toggle()  # Toggle the LED state
    time.sleep(0.1)    # Wait for 1 second
