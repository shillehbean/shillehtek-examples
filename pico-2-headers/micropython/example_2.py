# Read the RP2350 internal temperature sensor via ADC(4), convert the ADC reading to degrees Celsius, and print once per second.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2-usb-c-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2-usb-c-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# Raspberry Pi Pico 2 - Read the internal temperature sensor
# The RP2350 has a built-in temperature sensor on ADC channel 4

from machine import ADC
import time

sensor_temp = ADC(4)
conversion_factor = 3.3 / 65535

while True:
    reading = sensor_temp.read_u16() * conversion_factor
    # Formula from the RP2350 datasheet
    temperature = 27 - (reading - 0.706) / 0.001721
    print("Temperature: {:.2f} C".format(temperature))
    time.sleep(1)
