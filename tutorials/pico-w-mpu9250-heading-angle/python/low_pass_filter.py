# Implements a simple exponential low-pass filter function that blends a previous value with a new measurement.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-mpu9250-heading-angle
# Parts used: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

def low_pass_filter(prev_value, new_value):
    return 0.85 * prev_value + 0.15 * new_value
