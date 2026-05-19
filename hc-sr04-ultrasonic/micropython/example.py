# Runs on a MicroPython board (e.g., Pico) using GP15 (Trig) and GP14 (Echo) to send a trigger, measure the echo with time_pulse_us, and print the distance in centimeters.
#
# Buy this module: https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# HC-SR04 Ultrasonic Distance Sensor - Pico MicroPython Example
# Trig Pin: GP15, Echo Pin: GP14

from machine import Pin, time_pulse_us
import time

trigPin = Pin(15, Pin.OUT)
echoPin = Pin(14, Pin.IN)

while True:
    # Send trigger pulse
    trigPin.value(0)
    time.sleep_us(2)
    trigPin.value(1)
    time.sleep_us(10)
    trigPin.value(0)

    # Measure pulse duration
    try:
        pulse_duration = time_pulse_us(echoPin, 1, 30000)
    except OSError:
        print("Timeout waiting for echo")
        continue

    # Calculate distance in cm
    distance = pulse_duration * 0.0343 / 2

    print("Distance: {:.2f} cm".format(distance))
    time.sleep(0.5)
