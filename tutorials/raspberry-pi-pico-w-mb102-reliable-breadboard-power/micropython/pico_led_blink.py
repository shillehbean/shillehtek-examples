# Blink the Raspberry Pi Pico W onboard LED on the 'LED' pin with 0.2 second on/off intervals to verify power and wiring.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mb102-reliable-breadboard-power
# Parts used: https://shillehtek.com/products/shillehtek-universal-power-supply-module
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import machine
import time

# Initialize the onboard LED (usually on pin 25 for Pico W)
led = machine.Pin("LED", machine.Pin.OUT)

# Blink the LED every 0.2 seconds
while True:
    led.on()        # Turn the LED on
    time.sleep(0.2) # Wait for 0.2 seconds
    led.off()       # Turn the LED off
    time.sleep(0.2) # Wait for 0.2 seconds
