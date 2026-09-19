# Use MicroPython PWM on GP15 to control the coin motor's duty cycle for taps, sustained buzzes, and a rising-alert ramp on 3.3V-powered hardware.
#
# Buy this module: https://shillehtek.com/products/coin-vibration-motor-1027-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/coin-vibration-motor-1027-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Coin motor via transistor on GP15, motor powered from 3V3.

from machine import Pin, PWM
import time

motor = PWM(Pin(15))
motor.freq(1000)

def vibe(percent, ms):
    motor.duty_u16(int(65535 * percent / 100))
    time.sleep_ms(ms)
    motor.duty_u16(0)

while True:
    vibe(100, 80)          # tap
    time.sleep(1)
    vibe(60, 300)          # soft buzz
    time.sleep(1)
    for p in range(30, 101, 10):   # rising alert
        motor.duty_u16(int(65535 * p / 100))
        time.sleep_ms(40)
    motor.duty_u16(0)
    time.sleep(2)
