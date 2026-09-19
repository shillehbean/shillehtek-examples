# Uses gpiozero on a Raspberry Pi to turn each SSR channel on for 1 second in sequence and ensures all channels are turned off on KeyboardInterrupt.
#
# Buy this module: https://shillehtek.com/products/4-channel-5v-ssr-module-arduino-esp32-raspberry
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/4-channel-5v-ssr-module-arduino-esp32-raspberry-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from gpiozero import DigitalOutputDevice
from time import sleep

# active_high=True: HIGH turns the channel on
channels = [DigitalOutputDevice(pin, active_high=True, initial_value=False)
            for pin in (17, 27, 22, 23)]

try:
    while True:
        for i, ch in enumerate(channels, start=1):
            ch.on()
            print(f"Channel {i} ON")
            sleep(1)
            ch.off()
except KeyboardInterrupt:
    for ch in channels:
        ch.off()
