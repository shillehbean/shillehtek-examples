# ESP32 MicroPython example that reads the pot on GPIO34 with averaging, converts to percent, sets LED PWM on GPIO25, and prints the readings.
#
# Buy this module: https://shillehtek.com/products/slide-potentiometer-module-10k-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/slide-potentiometer-module-10k-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 10K Slide Potentiometer - ESP32 MicroPython Example
# OTA->GPIO 34, VCC->3V3, GND->GND, optional LED on GPIO 25

from machine import ADC, Pin, PWM
import time

adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)          # full 0-3.3V range
led = PWM(Pin(25), freq=1000)

def read_smooth(n=16):
    return sum(adc.read() for _ in range(n)) // n   # 0..4095

print("Slide the fader!")
while True:
    raw = read_smooth()
    percent = raw * 100 // 4095
    led.duty(raw >> 2)            # 0..1023 duty

    print("Raw: {:4d} | Position: {:3d} %".format(raw, percent))
    time.sleep(0.1)
