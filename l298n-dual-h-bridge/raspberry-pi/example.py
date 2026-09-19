# Raspberry Pi (gpiozero) Python example that drives two DC motors with direction provided by Motor and speed by PWMOutputDevice, cycling forward, reverse, and stop.
#
# Buy this module: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/l298n-motor-driver-controller-board-module-for-stepper-motor-dc-dual-h-bridge
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# L298N on Raspberry Pi - drive 2 DC motors with PWM
# Install: pip install gpiozero

from gpiozero import Motor, PWMOutputDevice
from time import sleep

# gpiozero's Motor handles direction; we add PWM for speed
motor_a = Motor(forward=23, backward=24)
speed_a = PWMOutputDevice(12)

motor_b = Motor(forward=27, backward=22)
speed_b = PWMOutputDevice(13)

def drive(motor, speed_pin, speed):
    if speed > 0:
        motor.forward()
    elif speed < 0:
        motor.backward()
    else:
        motor.stop()
    speed_pin.value = abs(speed)

try:
    while True:
        drive(motor_a, speed_a, 0.8); drive(motor_b, speed_b, 0.8); sleep(2)
        drive(motor_a, speed_a, -0.6); drive(motor_b, speed_b, -0.6); sleep(2)
        drive(motor_a, speed_a, 0);   drive(motor_b, speed_b, 0);   sleep(1)
except KeyboardInterrupt:
    pass
