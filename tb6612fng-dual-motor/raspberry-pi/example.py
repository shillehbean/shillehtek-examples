# Use gpiozero on a Raspberry Pi to enable the TB6612FNG standby pin and control a motor with forward, backward, and stop commands using gpiozero's Motor abstraction.
#
# Buy this module: https://shillehtek.com/products/tb6612fng-dual-motor-driver-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tb6612fng-dual-motor-driver-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from gpiozero import Motor, DigitalOutputDevice
from time import sleep

# PWMA tied to 3.3 V; gpiozero PWMs the direction pins
stby = DigitalOutputDevice(22, initial_value=True)   # enable
motor = Motor(forward=17, backward=27)

while True:
    motor.forward(0.8)    # 80% speed
    sleep(2)
    motor.backward(0.4)   # 40% reverse
    sleep(2)
    motor.stop()
    sleep(1)
