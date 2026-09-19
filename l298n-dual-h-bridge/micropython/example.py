# MicroPython script for Raspberry Pi Pico using machine.PWM and GPIO to set direction and PWM speed for two DC motors connected to an L298N.
#
# Buy this module: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/l298n-motor-driver-controller-board-module-for-stepper-motor-dc-dual-h-bridge
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# L298N on Raspberry Pi Pico - two DC motors

from machine import Pin, PWM
import time

ENA = PWM(Pin(2)); IN1 = Pin(3, Pin.OUT); IN2 = Pin(4, Pin.OUT)
ENB = PWM(Pin(7)); IN3 = Pin(5, Pin.OUT); IN4 = Pin(6, Pin.OUT)

ENA.freq(20000); ENB.freq(20000)

def motor(en, in1, in2, speed):
    # speed in -65535..65535
    in1.value(1 if speed > 0 else 0)
    in2.value(1 if speed < 0 else 0)
    en.duty_u16(min(abs(speed), 65535))

while True:
    motor(ENA, IN1, IN2,  50000); motor(ENB, IN3, IN4,  50000); time.sleep(2)
    motor(ENA, IN1, IN2, -40000); motor(ENB, IN3, IN4, -40000); time.sleep(2)
    motor(ENA, IN1, IN2,  0);     motor(ENB, IN3, IN4,  0);     time.sleep(1)
