# Toggles GPIO18 on a Raspberry Pi using RPi.GPIO to switch the pump on for 5 seconds and off for 55 seconds in a loop, assuming the pump is powered from the Pi's 5V rail or an external 5V supply.
#
# Buy this module: https://shillehtek.com/products/mini-submersible-water-pump-5v-120lph-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-submersible-water-pump-5v-120lph-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Raspberry Pi controls the pump through a MOSFET or relay on GPIO 18.
# Pump power from the Pi's 5V pin (short runs) or an external 5V supply.

import RPi.GPIO as GPIO
import time

PUMP = 18
GPIO.setmode(GPIO.BCM)
GPIO.setup(PUMP, GPIO.OUT)

try:
    while True:
        print("Pump ON")
        GPIO.output(PUMP, GPIO.HIGH)
        time.sleep(5)          # circulate for 5 s
        print("Pump OFF")
        GPIO.output(PUMP, GPIO.LOW)
        time.sleep(55)         # rest for 55 s
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
