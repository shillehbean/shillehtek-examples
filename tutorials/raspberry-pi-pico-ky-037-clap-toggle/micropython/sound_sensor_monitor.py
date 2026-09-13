# Simple MicroPython test script that continuously reads the KY-037 digital output, prints the value, and mirrors it to the onboard LED so you can verify sensor behavior.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-ky-037-clap-toggle
# Parts used: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

sound = Pin(15, Pin.IN)      # KY-037 DO -> GP15
led = Pin("LED", Pin.OUT)

while True:
    v = sound.value()
    print("DO:", v)
    led.value(v)             # LED ON when DO is HIGH
    time.sleep(0.05)
