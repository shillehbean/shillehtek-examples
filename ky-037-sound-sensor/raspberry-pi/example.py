# Uses gpiozero to monitor the KY-037 DO pin on a Raspberry Pi (GPIO17) and prints a notification when the module's digital output goes LOW (sound detected), with basic debounce.
#
# Buy this module: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-037-sound-sensor-module-with-analog
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# KY-037 digital trigger on Raspberry Pi
# Install: pip install gpiozero

from gpiozero import DigitalInputDevice
from time import sleep

sound = DigitalInputDevice(17)  # DO pin

print("Listening for sound... (Ctrl+C to quit)")
while True:
    if not sound.value:   # LOW = above threshold on KY-037
        print("Sound detected!")
        sleep(0.2)        # debounce
    sleep(0.01)
