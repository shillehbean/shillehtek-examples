# Raspberry Pi Python script using gpiozero that treats the relay as active-low (active_high=False) and toggles GPIO17 on/off every 5 seconds, with clean shutdown on Ctrl+C.
#
# Buy this module: https://shillehtek.com/products/solid-state-relay-1ch-5v-active-low
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/solid-state-relay-1ch-5v-active-low-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from gpiozero import DigitalOutputDevice
from time import sleep

# active_high=False: on() pulls CH low, which turns the SSR on
relay = DigitalOutputDevice(17, active_high=False, initial_value=False)

try:
    while True:
        relay.on()
        print("Load ON")
        sleep(5)
        relay.off()
        print("Load OFF")
        sleep(5)
except KeyboardInterrupt:
    relay.off()
