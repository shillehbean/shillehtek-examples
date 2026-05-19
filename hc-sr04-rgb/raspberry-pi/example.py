# Uses Raspberry Pi GPIO and rpi_ws281x to ping the HC‑SR04, print distance readings, and drive the onboard NeoPixels to show a color based on range.
#
# Buy this module: https://shillehtek.com/products/shillehtek-hc-sr04-with-rgb-light-distance
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-hc-sr04-with-rgb-light-distance-manual
# More examples: https://github.com/shillehtek/examples
#

# Install: sudo pip3 install rpi_ws281x --break-system-packages
# Run:     sudo python3 hcsr04_rgb.py
# Wiring:  Trig=GPIO23, Echo=GPIO24 (via divider), RGB_IN=GPIO18 (via shifter).

import time
import RPi.GPIO as GPIO
from rpi_ws281x import PixelStrip, Color

TRIG = 23
ECHO = 24

NUM_LEDS  = 4
LED_PIN   = 18        # must be PWM-capable
LED_FREQ  = 800000
LED_DMA   = 10
LED_INV   = False
LED_BRT   = 40
LED_CH    = 0

strip = PixelStrip(NUM_LEDS, LED_PIN, LED_FREQ, LED_DMA, LED_INV, LED_BRT, LED_CH)
strip.begin()

GPIO.setmode(GPIO.BCM)
GPIO.setup(TRIG, GPIO.OUT, initial=GPIO.LOW)
GPIO.setup(ECHO, GPIO.IN)

def ping_cm():
    GPIO.output(TRIG, True); time.sleep(1e-5); GPIO.output(TRIG, False)
    t0 = time.time()
    while GPIO.input(ECHO) == 0 and time.time() - t0 < 0.03: start = time.time()
    while GPIO.input(ECHO) == 1 and time.time() - t0 < 0.06: stop  = time.time()
    try:
        return (stop - start) * 17150.0
    except UnboundLocalError:
        return -1.0

def set_all(color):
    for i in range(NUM_LEDS):
        strip.setPixelColor(i, color)
    strip.show()

try:
    while True:
        cm = ping_cm()
        print(f"Distance: {cm:.1f} cm")
        if cm < 0:        set_all(Color(0, 0, 50))
        elif cm < 15:     set_all(Color(255, 0, 0))
        elif cm < 50:     set_all(Color(255, 120, 0))
        else:             set_all(Color(0, 200, 0))
        time.sleep(0.1)
except KeyboardInterrupt:
    set_all(Color(0, 0, 0))
    GPIO.cleanup()
