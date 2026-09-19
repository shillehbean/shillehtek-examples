# Raspberry Pi Pico MicroPython example that averages ADC0 readings on GP26, computes percent, drives an LED on GP15 with 16-bit PWM, and prints values.
#
# Buy this module: https://shillehtek.com/products/slide-potentiometer-module-10k-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/slide-potentiometer-module-10k-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 10K Slide Potentiometer - Pico MicroPython Example
# OTA->GP26 (ADC0), VCC->3V3(OUT), GND->GND
# Optional LED on GP15 via 220 ohm

from machine import ADC, Pin, PWM
import time

adc = ADC(26)
led = PWM(Pin(15))
led.freq(1000)

def read_smooth(n=16):
    return sum(adc.read_u16() for _ in range(n)) // n   # 0..65535

print("Slide the fader!")
while True:
    raw = read_smooth()
    percent = raw * 100 // 65535
    led.duty_u16(raw)             # direct 16-bit dimming

    print("Raw: {:5d} | Position: {:3d} %".format(raw, percent))
    time.sleep(0.1)
