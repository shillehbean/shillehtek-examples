# Toggles the Pico/Pico W onboard LED once using the machine.Pin API.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-rshell-repl-led-blink
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
led = Pin("LED", Pin.OUT)
led.toggle()
