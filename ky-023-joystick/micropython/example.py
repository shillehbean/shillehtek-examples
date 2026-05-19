# MicroPython example for a Pico: reads 16-bit ADC values for X and Y and the switch state, printing them periodically over the REPL/serial connection.
#
# Buy this module: https://shillehtek.com/products/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# KY-023 on Raspberry Pi Pico (MicroPython)
# VRX -> GP26, VRY -> GP27, SW -> GP15, +5V -> 3V3, GND -> GND

from machine import ADC, Pin
import time

x_axis = ADC(Pin(26))
y_axis = ADC(Pin(27))
sw     = Pin(15, Pin.IN, Pin.PULL_UP)

while True:
    # 16-bit values (0 - 65535)
    x = x_axis.read_u16()
    y = y_axis.read_u16()
    btn = "PRESSED" if sw.value() == 0 else "released"
    print("X:", x, " Y:", y, " SW:", btn)
    time.sleep(0.1)
