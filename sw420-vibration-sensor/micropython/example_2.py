# On a Raspberry Pi Pico running MicroPython, attach an IRQ on GP15 to count vibration pulses and print a per-second summary of vibration strength.
#
# Buy this module: https://shillehtek.com/products/vibration-sensor-sw-420-arduino-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vibration-sensor-sw-420-arduino-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# SW-420 Vibration Sensor - Pico MicroPython Example
# DO -> GP15, VCC -> 3V3(OUT), GND -> GND

from machine import Pin
import time

sensor = Pin(15, Pin.IN)
pulse_count = 0

def on_vibration(pin):
    global pulse_count
    pulse_count += 1

sensor.irq(trigger=Pin.IRQ_RISING | Pin.IRQ_FALLING, handler=on_vibration)

print("Monitoring vibration...")

while True:
    pulse_count = 0
    time.sleep(1)

    if pulse_count == 0:
        print("Still")
    elif pulse_count < 20:
        print("Light vibration  ({} pulses)".format(pulse_count))
    else:
        print("STRONG vibration ({} pulses)".format(pulse_count))
