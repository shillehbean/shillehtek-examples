# MicroPython script for the Raspberry Pi Pico that uses two PWM outputs to drive, brake, and reverse a DC motor via the DRV8871.
#
# Buy this module: https://shillehtek.com/products/drv8871-h-bridge-motor-driver-module-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/drv8871-h-bridge-motor-driver-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# DRV8871 motor driver on Raspberry Pi Pico (MicroPython) - forward, brake, reverse
# Wiring: IN1 = GP14, IN2 = GP15, GND = GND
# The motor supply (6.5 V to 45 V) goes to POWER + and POWER -. Leave the header VM pin unconnected.
from machine import Pin, PWM
import time

in1 = PWM(Pin(14))
in2 = PWM(Pin(15))
in1.freq(20000)           # 20 kHz, above the audible range
in2.freq(20000)


def drive(speed):         # speed: -1.0 (full reverse) to 1.0 (full forward)
    duty = int(min(abs(speed), 1.0) * 65535)
    if speed >= 0:
        in1.duty_u16(duty)
        in2.duty_u16(0)
    else:
        in1.duty_u16(0)
        in2.duty_u16(duty)


def brake():              # both inputs high = brake
    in1.duty_u16(65535)
    in2.duty_u16(65535)


while True:
    drive(0.5)
    time.sleep(2)
    drive(1.0)
    time.sleep(2)
    brake()
    time.sleep(1)
    drive(-0.5)
    time.sleep(2)
    drive(0)              # both inputs low = coast
    time.sleep(2)
