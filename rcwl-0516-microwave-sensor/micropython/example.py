# MicroPython example for a Pico: attach an IRQ to the RCWL-0516 to count motion events and mirror the sensor state to the onboard LED.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rcwl-0516-microwave-doppler-radar-motion-sensor-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

sensor = Pin(15, Pin.IN)
led    = Pin(25, Pin.OUT)   # onboard LED

motion_count = 0

def on_motion(pin):
    global motion_count
    motion_count += 1
    print("Motion #%d" % motion_count)

sensor.irq(trigger=Pin.IRQ_RISING, handler=on_motion)

print("RCWL-0516 on Pico ready")
while True:
    led.value(sensor.value())  # Mirror state to onboard LED
    time.sleep_ms(50)
