# Reads the HC-SR501 PIR sensor on GPIO0 and toggles an LED on GPIO2 with a debounce interval to indicate motion detection.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-hc-sr501-motion-led
# Parts used: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

# Initialize PIR sensor on GPIO 0
pir = Pin(0, Pin.IN, Pin.PULL_DOWN)
led = Pin(2, Pin.OUT)  # Initialize LED on GPIO 2
pir_state = False  # Start assuming no motion detected
last_motion_time = 0  # Timestamp of the last motion detected
debounce_time = 3  # Debounce period in seconds

print("PIR Module Initialized")
time.sleep(1)  # Allow the sensor to stabilize
print("Ready")

while True:
    val = pir.value()  # Read input value from PIR sensor
    current_time = time.time()

    if val == 1:  # Motion detected
        if not pir_state and (current_time - last_motion_time >= debounce_time):
            print(current_time - last_motion_time)
            print("Motion detected!")
            pir_state = True
            led.on()  # Turn on LED
            last_motion_time = current_time  # Update the last motion timestamp

    elif val == 0:
        if pir_state and (current_time - last_motion_time >= debounce_time):
            pir_state = False
            led.off()
            last_motion_time = current_time  # Update the last motion timestamp

    time.sleep(0.1)  # Small delay to prevent spamming
