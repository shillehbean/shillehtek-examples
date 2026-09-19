# Raspberry Pi Pico MicroPython example that samples ADC0 (GP26), calibrates the zero-voltage baseline, converts readings to gauss, and prints field strength and pole to the REPL.
#
# Buy this module: https://shillehtek.com/products/linear-hall-effect-sensor-49e-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/linear-hall-effect-sensor-49e-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# 49E Linear Hall Effect Sensor - Pico MicroPython Example
# OUT -> GP26 (ADC0), VCC -> 3V3(OUT), GND -> GND

from machine import ADC
import time

adc = ADC(26)
CONVERSION = 3.3 / 65535
MV_PER_GAUSS = 0.9        # ~0.9 mV/G at 3.3V supply

def read_volts(samples):
    total = 0
    for _ in range(samples):
        total += adc.read_u16()
        time.sleep_ms(2)
    return total / samples * CONVERSION

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
