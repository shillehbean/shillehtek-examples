# ESP32 MicroPython script that samples GPIO34 with full-range ADC, calibrates the zero point, converts voltage to gauss, and prints readings and detected pole to the REPL.
#
# Buy this module: https://shillehtek.com/products/linear-hall-effect-sensor-49e-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/linear-hall-effect-sensor-49e-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 49E Linear Hall Effect Sensor - ESP32 MicroPython Example
# OUT -> GPIO 34, VCC -> 3V3, GND -> GND

from machine import ADC, Pin
import time

adc = ADC(Pin(34))
adc.atten(ADC.ATTN_11DB)      # full 0-3.3V range

MV_PER_GAUSS = 0.9            # ratiometric: ~0.9 mV/G at 3.3V supply

def read_volts(samples):
    total = 0
    for _ in range(samples):
        total += adc.read_uv()
        time.sleep_ms(2)
    return total / samples / 1_000_000

print("Calibrating - keep magnets away...")
time.sleep(1)
zero = read_volts(200)
print("Zero point: {:.3f} V. Bring a magnet close!".format(zero))

while True:
    volts = read_volts(20)
    gauss = (volts - zero) * 1000 / MV_PER_GAUSS

    if gauss > 15:
        pole = "south pole"
    elif gauss < -15:
        pole = "north pole"
    else:
        pole = "no field"

    print("OUT: {:.3f} V | ~{:.0f} G ({})".format(volts, gauss, pole))
    time.sleep(0.3)
