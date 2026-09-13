# Uses gpiozero's RotaryEncoder and Button classes on a Raspberry Pi to print knob step counts and detect button presses via event callbacks.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-040-rotary-encoder-module-for-arduino-with-demo-code-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# KY-040 Rotary Encoder - Raspberry Pi Example
# CLK=GPIO17, DT=GPIO27, SW=GPIO22

from gpiozero import RotaryEncoder, Button
from signal import pause

rotor = RotaryEncoder(17, 27, max_steps=0)
button = Button(22, pull_up=True)

def turned():
    print("Count: {}".format(rotor.steps))

def pressed():
    print("Button pressed!")

rotor.when_rotated = turned
button.when_pressed = pressed

print("Turn the knob or press the button. Ctrl+C to quit.")
pause()
