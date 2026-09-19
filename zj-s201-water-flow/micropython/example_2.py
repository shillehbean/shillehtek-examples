# Raspberry Pi Pico MicroPython example that counts pulses on GP15 to compute flow and total volume and uses the onboard LED as a simple leak alarm when flow exceeds a small threshold.
#
# Buy this module: https://shillehtek.com/products/water-flow-sensor-g1-2-1-30l-min
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/water-flow-sensor-g1-2-1-30l-min-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ZJ-S201 Water Flow Sensor - Pico MicroPython Example
# Yellow->GP15, Red->VBUS(5V), Black->GND
# Includes a simple leak alarm: flow when there shouldn't be any.

from machine import Pin
import time

pulses = 0
def on_pulse(pin):
    global pulses
    pulses += 1

flow = Pin(15, Pin.IN, Pin.PULL_UP)
flow.irq(trigger=Pin.IRQ_FALLING, handler=on_pulse)
led = Pin("LED", Pin.OUT)

PULSES_PER_LMIN = 7.5
total_liters = 0.0

print("Flow meter ready - open the tap!")
while True:
    pulses = 0
    time.sleep(1)
    lmin = pulses / PULSES_PER_LMIN
    total_liters += lmin / 60

    led.value(1 if lmin > 0.2 else 0)   # LED on while water flows
    print("Flow: {:.2f} L/min | Total: {:.3f} L".format(lmin, total_liters))
