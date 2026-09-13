# MicroPython script for a Raspberry Pi Pico W that measures distance with an HC-SR04 and updates Neopixel LEDs to indicate proximity and display random color patterns.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-hc-sr04-obstacle-detection
# Parts used: https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

"""
This script uses an ultrasonic sensor (HC-SR04) and Neopixel LEDs on a Raspberry Pi Pico.
It measures distance using the ultrasonic sensor and changes the LED colors based on proximity:
- Red (<10 cm)
- Yellow (10-20 cm)
- Green (>20 cm)

Additionally, it includes a function to randomly light up LEDs with different colors.

Module used:
https://www.amazon.com/Ultrasonic-Compatible-Distance-Avoidance-Raspberry/dp/B0BRMP73C2

Neopixel helper library found at shillehtek.com
"""

from machine import Pin, time_pulse_us
import random
import time

from neopixel import Neopixel

# Initialize ultrasonic sensor pins and Neopixel LEDs.
# Defines trigger/echo pins for distance measurement and sets up LED colors.
SOUND_SPEED = 340
TRIG_PULSE_DURATION_US = 10
TRIG_PIN = Pin(15, Pin.OUT)
ECHO_PIN = Pin(14, Pin.IN)

# Set params for Neopixel
NUMPIX = 6
PIXELS = Neopixel(NUMPIX, 0, 28)

# Define LED colors
YELLOW = (255, 100, 0)
ORANGE = (255, 50, 0)
GREEN  = (0, 255, 0)
BLUE   = (0, 0, 255)
RED    = (255, 0, 0)
LAVENDER = (230, 230, 250)

# Color dictionary for assigning random colors
COLOR_DICT = {
    0: YELLOW,
    1: ORANGE,
    2: GREEN,
    3: BLUE,
    4: RED,
    5: LAVENDER
}

def get_distance():
    '''Returns distance in centimeters'''
    TRIG_PIN.value(0)
    time.sleep_us(5)
    TRIG_PIN.value(1)
    time.sleep_us(TRIG_PULSE_DURATION_US)
    TRIG_PIN.value(0)

    ultrason_duration = time_pulse_us(ECHO_PIN, 1, 30000)  # 30ms timeout
    distance_cm = SOUND_SPEED * ultrason_duration / 20000
    print(f"Distance : {distance_cm} cm")
    return distance_cm

def change_color_with_distance():
    '''
    Continuously measures distance and changes LED color based on proximity:
    - <10 cm: RED
    - 10–20 cm: YELLOW
    - >20 cm: GREEN
    '''
    while True:
        distance = get_distance()
        if distance < 10:
            color = RED
        elif distance < 20:
            color = YELLOW
        else:
            color = GREEN

        # Set all 6 LEDs to the same color
        for i in range(NUMPIX):
            PIXELS.set_pixel(i, color)
        PIXELS.show()

        time.sleep(1)

def fun():
    '''
    Loops through random colors for the 6 LEDs.
    Demonstrates how to randomly assign colors and
    can be modified further for brightness, effects, etc.
    '''
    while True:
        random_led = random.randint(0, 5)
        random_color = random.randint(0, len(COLOR_DICT) - 1)
        print(random_led, COLOR_DICT[random_color])

        PIXELS.set_pixel(random_led, COLOR_DICT[random_color])
        PIXELS.show()

        time.sleep(0.5)

# Start the main distance-based color function:
change_color_with_distance()
