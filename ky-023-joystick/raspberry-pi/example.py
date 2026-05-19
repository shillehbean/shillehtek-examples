# Python example for Raspberry Pi using an MCP3008 (gpiozero): reads normalized axis values and a GPIO button, then prints formatted values to the console.
#
# Buy this module: https://shillehtek.com/products/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-023-dual-axis-joystick-module-ps2-analog-sensor-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# KY-023 on Raspberry Pi via MCP3008 ADC
# pip install gpiozero

from gpiozero import MCP3008, Button
import time

x_axis = MCP3008(channel=0)   # 0.0 - 1.0
y_axis = MCP3008(channel=1)
button = Button(17)           # GPIO 17

while True:
    x = x_axis.value
    y = y_axis.value
    pressed = button.is_pressed
    print(f"X: {x:.2f}  Y: {y:.2f}  SW: {'PRESSED' if pressed else 'released'}")
    time.sleep(0.1)
