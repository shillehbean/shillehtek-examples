# Runs on a Raspberry Pi using RPi.GPIO event detection to print timestamped motion events from the RCWL-0516 via a callback.
#
# Buy this module: https://shillehtek.com/products/Arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rcwl-0516-microwave-doppler-radar-motion-sensor-module-manual
# More examples: https://github.com/shillehtek/examples
#

import RPi.GPIO as GPIO
import time
from datetime import datetime

SENSOR_PIN = 17

GPIO.setmode(GPIO.BCM)
GPIO.setup(SENSOR_PIN, GPIO.IN)

def on_motion(channel):
    print(f"[{datetime.now().isoformat(timespec='seconds')}] Motion detected")

GPIO.add_event_detect(SENSOR_PIN, GPIO.RISING, callback=on_motion, bouncetime=200)

print("RCWL-0516 reader started. Ctrl-C to exit.")
try:
    while True:
        time.sleep(1)
except KeyboardInterrupt:
    pass
finally:
    GPIO.cleanup()
