# Runs on MicroPython (e.g., Pico) to read the MQ-7 on ADC0 (GP26), convert the 16-bit ADC value to volts with divider compensation, and print the sensor voltage in a loop.
#
# Buy this module: https://shillehtek.com/products/mq-7-co-gas-sensor-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-7-co-gas-sensor-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import ADC
import time

# MQ-7 A0 -> 10k/20k divider -> GP26 (ADC0)
adc = ADC(26)
DIVIDER = 1.5

print("MQ-7 warming up - readings stabilize after several minutes")
while True:
    raw = adc.read_u16()
    v_adc = raw * 3.3 / 65535
    v_sensor = v_adc * DIVIDER
    print("Sensor voltage: {:.2f} V".format(v_sensor))
    time.sleep(1)
