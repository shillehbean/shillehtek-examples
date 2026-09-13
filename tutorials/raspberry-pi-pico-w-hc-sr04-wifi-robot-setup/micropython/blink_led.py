# Blinks the onboard LED on a Raspberry Pi Pico W using the machine.Pin interface.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-hc-sr04-wifi-robot-setup
# Parts used: https://shillehtek.com/products/shillehtek-hc-sr04-with-rgb-light-distance
#             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
from time import sleep

# The onboard LED on the Pico W is connected to GP25
led = Pin("LED", Pin.OUT)

# Blink the LED
while True:
    led.value(1)  # Turn the LED on
    sleep(1)      # Wait for 1 second
    led.value(0)  # Turn the LED off
    sleep(1)      # Wait for 1 second
