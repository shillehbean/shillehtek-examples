# Use MicroPython on an ESP32 to attach an IRQ to GPIO25, increment a pulse counter on both edges, and print a per-second vibration status message.
#
# Buy this module: https://shillehtek.com/products/vibration-sensor-sw-420-arduino-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vibration-sensor-sw-420-arduino-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# SW-420 Vibration Sensor - ESP32 MicroPython Example
# DO -> GPIO 25, VCC -> 3V3, GND -> GND

from machine import Pin
import time

sensor = Pin(25, Pin.IN)
pulse_count = 0

def on_vibration(pin):
    global pulse_count
    pulse_count += 1

# Trigger on both edges so idle-HIGH board revisions work too
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
