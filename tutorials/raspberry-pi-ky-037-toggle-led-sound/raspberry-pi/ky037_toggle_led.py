# Monitors the KY-037 digital output on GPIO4 and toggles an LED on GPIO17 when sound is detected, printing the LED state and using a 1 second debounce.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-ky-037-toggle-led-sound
# Parts used: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

import RPi.GPIO as GPIO
import time

# Set up GPIO pin numbering mode and define pins for sensor and LED
GPIO.setmode(GPIO.BCM)
SOUND_SENSOR_PIN = 4  # GPIO pin number connected to D0 pin of KY-037
LED_PIN = 17  # GPIO pin number connected to LED

# Set up the pins
GPIO.setup(SOUND_SENSOR_PIN, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)  # Configure sound sensor pin as input
GPIO.setup(LED_PIN, GPIO.OUT)  # Configure LED pin as output

# Initialize LED state
led_state = False

# Function to toggle LED based on sound detection
def toggle_led():
    global led_state
    if led_state:
        GPIO.output(LED_PIN, GPIO.LOW)  # Turn off the LED
        print("LED turned OFF")
    else:
        GPIO.output(LED_PIN, GPIO.HIGH)  # Turn on the LED
        print("LED turned ON")
    led_state = not led_state  # Toggle the state

# Main loop to check for sound detection and toggle LED
try:
    print("Starting sound sensor program. Snap or clap to toggle the LED.")
    while True:
        if GPIO.input(SOUND_SENSOR_PIN) == 1:  # Sound detected
            toggle_led()
            time.sleep(1)  # Wait for a second to avoid multiple toggles on one sound
except KeyboardInterrupt:
    print("Program interrupted. Cleaning up GPIO settings.")
finally:
    GPIO.cleanup()  # Clean up all GPIO settings
