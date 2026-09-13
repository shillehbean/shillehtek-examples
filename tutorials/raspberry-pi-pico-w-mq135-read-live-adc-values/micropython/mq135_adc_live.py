# Reads raw ADC values from an MQ-135 sensor connected to GP26 on a Raspberry Pi Pico W and prints them to the serial console once per second.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mq135-read-live-adc-values
# Parts used: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
#             https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import ADC
import time

mq135 = ADC(26)  # GP26 = ADC0

while True:
    raw_value = mq135.read_u16()  # 0 to 65535
    print("MQ135 Analog Value:", raw_value)
    time.sleep(1)
