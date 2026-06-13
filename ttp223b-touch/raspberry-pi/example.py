# Uses gpiozero on a Raspberry Pi with GPIO17 to call event handlers that print 'Touched' and 'Released' when the TTP223 changes state.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/digital-sensor-ttp223b-module-capacitive-touch-switch-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# TTP223B Capacitive Touch Switch - Raspberry Pi Example
# Uses gpiozero's Button class for clean event handling.
# SIG: GPIO 17 (physical pin 11)

from gpiozero import Button
from signal import pause

touch = Button(17, pull_up=False)

def on_touch():
    print("Touched")

def on_release():
    print("Released")

touch.when_pressed = on_touch
touch.when_released = on_release

print("TTP223B ready. Touch the pad...")
pause()
