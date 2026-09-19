# MicroPython code for a Pico that reads the KY-037 analog loudness via ADC0 and the digital threshold pin, prints the readings, and toggles the onboard LED when sound is detected.
#
# Buy this module: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-037-sound-sensor-module-with-analog
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# KY-037 on Pico - analog loudness + digital threshold

from machine import ADC, Pin
import time

analog  = ADC(Pin(26))           # GP26 = ADC0
digital = Pin(15, Pin.IN)
led     = Pin(25, Pin.OUT)       # onboard LED

while True:
    level = analog.read_u16()    # 0..65535
    trig  = digital.value()
    print("Level: {:5d}  Trigger: {}".format(
          level, "SOUND!" if trig == 0 else "quiet"))
    led.value(0 if trig == 0 else 1)
    time.sleep_ms(50)
