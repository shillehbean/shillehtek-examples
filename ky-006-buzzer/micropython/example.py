# Uses PWM on a Raspberry Pi Pico GPIO to output a sequence of increasing frequencies (1000–2500 Hz) to the buzzer, then silences it.
#
# Buy this module: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects-manual
# More examples: https://github.com/shillehtek/examples
#

# KY-006 on Raspberry Pi Pico - PWM tone (MicroPython)
# Wire S to GP15, +Vin to 3V3 (OUT), - to GND

from machine import Pin, PWM
import time

buzzer = PWM(Pin(15))
buzzer.duty_u16(32768)        # 50% duty cycle

for freq in [1000, 1500, 2000, 2500]:
    buzzer.freq(freq)
    time.sleep(0.3)

buzzer.duty_u16(0)            # silence
buzzer.deinit()
