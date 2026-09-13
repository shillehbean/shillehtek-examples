# Blinks the Raspberry Pi Pico onboard LED on and off at 250 ms intervals.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-wokwi-simulate-projects-without-hardware
# Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
#             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MicroPython script for blinking an LED on the Raspberry Pi Pico

from machine import Pin
import time

# Check if the default LED pin is available
try:
    LED_PIN = Pin(Pin.PICO_DEFAULT_LED_PIN, Pin.OUT)
except AttributeError:
    # If PICO_DEFAULT_LED_PIN is not defined, use Pin 25 which is the default LED pin for the Pico
    LED_PIN = Pin(25, Pin.OUT)

# Blink the LED
while True:
    LED_PIN.value(1)  # Turn the LED on
    time.sleep(0.25)  # Wait for 250 milliseconds
    LED_PIN.value(0)  # Turn the LED off
    time.sleep(0.25)  # Wait for 250 milliseconds
