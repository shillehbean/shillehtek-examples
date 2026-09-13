# MicroPython script for Raspberry Pi Pico W that initializes the MPU9250 over I2C, calibrates the magnetometer, applies a low-pass filter to magnetometer readings, and converts the filtered readings into a heading angle and compass direction.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-mpu9250-heading-angle
# Parts used: https://shillehtek.com/products/shillehtek-mpu9250-authentic-gy-9250-pre-soldered
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import I2C, Pin
import math
import utime

from mpu9250 import MPU9250

i2c = I2C(0, sda=Pin(0), scl=Pin(1), freq=400000)
sensor = MPU9250(i2c)
filtered_magx, filtered_magy = 0, 0
DECLINATION = -1 * 3.19

# Want to thank Kevin McAleer

def low_pass_filter(prev_value, new_value):
    return 0.85 * prev_value + 0.15 * new_value


def compass(angle):
    if angle > 337 or angle <= 22:
        direction = 'North'
    elif angle > 22 and angle <= 67:
        direction = 'North East'
    elif angle > 67 and angle <= 112:
        direction = "East"
    elif angle > 112 and angle <= 157:
        direction = "South East"
    elif angle > 157 and angle <= 202:
        direction = "South"
    elif angle > 202 and angle <= 247:
        direction = "South West"
    elif angle > 247 and angle <= 292:
        direction = "West"
    elif angle > 292 and angle <= 337:
        direction = "North West"
    return direction


sensor.ak8963.calibrate()

while True:

    # We do not need the z value
    magx_new, magy_new, _ = sensor.magnetic

    filtered_magx = low_pass_filter(filtered_magx, magx_new)
    filtered_magy = low_pass_filter(filtered_magy, magy_new)

    heading_angle_in_degrees = math.atan2(filtered_magx, filtered_magy) * (180 / math.pi)
    heading_angle_in_degrees_plus_declination = heading_angle_in_degrees + DECLINATION

    if heading_angle_in_degrees_plus_declination < 0:
        heading_angle_in_degrees += 360
        heading_angle_in_degrees_plus_declination += 360

    print('###Without Declination###')
    print(heading_angle_in_degrees)
    print(compass(heading_angle_in_degrees))
    print('###Plus Declination###')
    print(heading_angle_in_degrees_plus_declination)
    print(compass(heading_angle_in_degrees_plus_declination))

    utime.sleep_ms(100)
