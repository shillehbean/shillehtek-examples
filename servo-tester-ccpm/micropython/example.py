# Run on a MicroPython board to produce 50 Hz servo pulses on GP15 (using duty_u16 conversion) and perform a neutral hold plus a full sweep from 800 to 2200 µs.
#
# Buy this module: https://shillehtek.com/products/servo-tester-rc-ccpm-checker
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/servo-tester-rc-ccpm-checker-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
import time

# Servo signal -> GP15, servo power from 5V (VBUS), common GND
pwm = PWM(Pin(15))
pwm.freq(50)

def write_us(us):
    # 50 Hz frame = 20000 us; duty_u16 is 0-65535
    pwm.duty_u16(int(us * 65535 / 20000))

while True:
    write_us(1500)      # neutral
    time.sleep(1)
    for us in range(800, 2201, 10):   # sweep up
        write_us(us)
        time.sleep(0.01)
    for us in range(2200, 799, -10):  # sweep down
        write_us(us)
        time.sleep(0.01)
