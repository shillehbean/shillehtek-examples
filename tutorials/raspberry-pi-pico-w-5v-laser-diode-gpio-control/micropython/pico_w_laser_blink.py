# Simple MicroPython script to blink the laser diode by toggling GPIO 0 on the Raspberry Pi Pico W (drives the transistor base through a resistor).
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-5v-laser-diode-gpio-control
# Parts used: https://shillehtek.com/products/shillehtek-universal-power-supply-module
#             https://shillehtek.com/products/shillehtek-6mm-650nm-5mw-red-laser-diode-module
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

# Initialize GPIO pin for the laser diode
laser = Pin(0, Pin.OUT)

# Function to blink the laser diode
while True:
    laser.value(1)  # Turn ON
    print("Laser ON")
    time.sleep(1)
    laser.value(0)  # Turn OFF
    print("Laser OFF")
    time.sleep(1)
