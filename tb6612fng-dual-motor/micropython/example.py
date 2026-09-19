# Use MicroPython to drive Motor A with a high-frequency PWM and two direction pins, providing a motor_a(speed) helper that accepts -1.0..1.0 and runs a simple forward/reverse/coast demo.
#
# Buy this module: https://shillehtek.com/products/tb6612fng-dual-motor-driver-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tb6612fng-dual-motor-driver-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
import time

pwma = PWM(Pin(15)); pwma.freq(20000)   # 20 kHz = silent
ain1 = Pin(14, Pin.OUT)
ain2 = Pin(13, Pin.OUT)
stby = Pin(12, Pin.OUT, value=1)        # enable

def motor_a(speed):
    """speed: -1.0 .. 1.0"""
    ain1.value(speed >= 0)
    ain2.value(speed < 0)
    pwma.duty_u16(int(abs(speed) * 65535))

while True:
    motor_a(0.8)     # forward
    time.sleep(2)
    motor_a(-0.5)    # reverse
    time.sleep(2)
    motor_a(0)       # coast
    time.sleep(1)
