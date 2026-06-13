# Runs on a Raspberry Pi Pico under MicroPython to read the battery via ADC, print the measured voltage, and flash the onboard LED quickly when the battery drops below a set threshold.
#
# Buy this module: https://shillehtek.com/products/Battery
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/cn3791-6v-mppt-solar-charger-module-manual
# More examples: https://github.com/shillehtek/examples
#

# CN3791 + Raspberry Pi Pico - MicroPython
# Wire BAT through 100k/100k divider to GP26 (ADC0).

from machine import ADC, Pin
import time

bat_adc = ADC(Pin(26))
led = Pin(25, Pin.OUT)

VREF = 3.3
DIVIDER_RATIO = 2.0
LOW_BAT = 3.3

def read_battery():
    # 16-bit ADC on Pico
    raw = bat_adc.read_u16()
    v_pin = (raw / 65535) * VREF
    return v_pin * DIVIDER_RATIO

while True:
    v = read_battery()
    print("Battery: {:.2f} V".format(v))

    if v < LOW_BAT:
        for _ in range(5):
            led.toggle()
            time.sleep(0.1)
    else:
        led.value(0)

    time.sleep(2)
