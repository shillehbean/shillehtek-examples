# MicroPython script for the Pico W that drives a 28BYJ-48 stepper motor via a ULN2003 driver using a full-step sequence, with functions to step, change direction, and release the motor.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-uln2003-stepper-control
# Parts used: https://shillehtek.com/products/shillehtek-5v-4-phase-stepper-motor-with-uln2003-driver
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
from time import sleep_ms

# ULN2003 inputs connected to Pico W
in1 = Pin(28, Pin.OUT)
in2 = Pin(27, Pin.OUT)
in3 = Pin(26, Pin.OUT)
in4 = Pin(22, Pin.OUT)

pins = [in1, in2, in3, in4]

# Full-step sequence for 28BYJ-48 through ULN2003
sequence = [
    [1, 0, 0, 0],
    [1, 1, 0, 0],
    [0, 1, 0, 0],
    [0, 1, 1, 0],
    [0, 0, 1, 0],
    [0, 0, 1, 1],
    [0, 0, 0, 1],
    [1, 0, 0, 1]
]

def set_step(step):
    for i in range(4):
        pins[i].value(step[i])

def step_motor(steps, delay_ms=2, direction=1):
    seq = sequence if direction == 1 else sequence[::-1]

    for _ in range(steps):
        for step in seq:
            set_step(step)
            sleep_ms(delay_ms)

def release_motor():
    for pin in pins:
        pin.value(0)

while True:
    # Roughly quarter turn depending on sequence and gearbox behavior
    step_motor(256, delay_ms=2, direction=1)
    sleep_ms(500)

    step_motor(256, delay_ms=2, direction=-1)
    sleep_ms(500)

    release_motor()
    sleep_ms(1000)
