# ESP32 MicroPython script that attaches a falling-edge IRQ on GPIO27 to count pulses, calculating and printing flow rate (L/min) and total volume each second.
#
# Buy this module: https://shillehtek.com/products/water-flow-sensor-g1-2-1-30l-min
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/water-flow-sensor-g1-2-1-30l-min-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ZJ-S201 Water Flow Sensor - ESP32 MicroPython Example
# Yellow->GPIO 27, Red->VIN(5V), Black->GND

from machine import Pin
import time

pulses = 0
def on_pulse(pin):
    global pulses
    pulses += 1

flow = Pin(27, Pin.IN, Pin.PULL_UP)
flow.irq(trigger=Pin.IRQ_FALLING, handler=on_pulse)

PULSES_PER_LMIN = 7.5
total_liters = 0.0

print("Flow meter ready - open the tap!")
while True:
    pulses = 0
    time.sleep(1)
    hz = pulses
    lmin = hz / PULSES_PER_LMIN
    total_liters += lmin / 60
    print("Flow: {:.2f} L/min | Total: {:.3f} L".format(lmin, total_liters))
