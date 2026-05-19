# Reads the analog voltage from A0 (GPIO1) via the ADC and prints the raw reading and converted voltage periodically.
#
# Buy this module: https://shillehtek.com/products/esp32-s3-nano-dev-board-presoldered-wifi-ble
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-s3-nano-dev-board-presoldered-wifi-ble-manual
# More examples: https://github.com/shillehtek/examples
#

# ESP32-S3 Nano - Read an analog value from A0 (GPIO1)
# Connect a potentiometer wiper to A0, ends to 3V3 and GND

from machine import ADC, Pin
import time

adc = ADC(Pin(1))                # A0 = GPIO1
adc.atten(ADC.ATTN_11DB)         # Full 0 - 3.3V range
adc.width(ADC.WIDTH_12BIT)       # 0 - 4095

while True:
    raw = adc.read()
    voltage = raw * 3.3 / 4095
    print("Raw: {:>4}   Voltage: {:.2f} V".format(raw, voltage))
    time.sleep(0.5)
