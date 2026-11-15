# Raspberry Pi (gpiozero) Python example that sets servo.value to different pulse widths to rotate the FS90R clockwise, stop, and rotate counterclockwise.
#
# Buy this module: https://shillehtek.com/products/fs90r-micro-servo-continuous-rotation
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fs90r-micro-servo-continuous-rotation-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# FS90R continuous rotation servo on Raspberry Pi with gpiozero
# Wiring: orange = GPIO 18 (pin 12), red = 5V (pin 2), brown = GND (pin 6)
from gpiozero import Servo
from time import sleep

# value 0 = 1.5 ms pulse = stop, -1 = 1.0 ms pulse, +1 = 2.0 ms pulse
servo = Servo(18, min_pulse_width=0.001, max_pulse_width=0.002)

while True:
    servo.value = -0.4      # 1.3 ms pulse: clockwise
    sleep(2)
    servo.value = 0         # stop
    sleep(1)
    servo.value = 0.4       # 1.7 ms pulse: counterclockwise
    sleep(2)
    servo.value = 0         # stop
    sleep(1)
