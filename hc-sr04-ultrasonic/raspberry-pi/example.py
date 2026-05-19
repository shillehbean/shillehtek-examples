# Uses Raspberry Pi GPIO 23 (Trig) and 24 (Echo) to trigger the HC-SR04, measure the echo pulse duration, and print distance in centimeters in a loop until interrupted.
#
# Buy this module: https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# HC-SR04 Ultrasonic Distance Sensor - Raspberry Pi Example
# Trig Pin: GPIO 23, Echo Pin: GPIO 24

import RPi.GPIO as GPIO
import time

trigPin = 23
echoPin = 24

GPIO.setmode(GPIO.BCM)
GPIO.setup(trigPin, GPIO.OUT)
GPIO.setup(echoPin, GPIO.IN)

try:
    while True:
        # Send trigger pulse
        GPIO.output(trigPin, GPIO.LOW)
        time.sleep(0.00001)
        GPIO.output(trigPin, GPIO.HIGH)
        time.sleep(0.00001)
        GPIO.output(trigPin, GPIO.LOW)

        # Wait for echo to start
        while GPIO.input(echoPin) == 0:
            pulse_start = time.time()

        # Wait for echo to end
        while GPIO.input(echoPin) == 1:
            pulse_end = time.time()

        # Calculate distance
        pulse_duration = pulse_end - pulse_start
        distance = pulse_duration * 17150  # cm

        print("Distance: {:.2f} cm".format(distance))
        time.sleep(0.5)

except KeyboardInterrupt:
    print("Measurement stopped by user")
finally:
    GPIO.cleanup()
