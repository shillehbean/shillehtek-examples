# MicroPython script for Raspberry Pi Pico that reads the KY-037 digital output and toggles a relay and the onboard LED when a clap/sound pulse is detected, using a cooldown debounce and an 'armed' re-arm on silence.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-ky-037-clap-toggle
# Parts used: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin
import time

SOUND_PIN = 15      # KY-037 DO -> GP15
RELAY_PIN = 16      # IoT Relay control -> GP16
COOLDOWN_MS = 1200  # buffer time between triggers (tune 800-1500)

sound = Pin(SOUND_PIN, Pin.IN)
relay = Pin(RELAY_PIN, Pin.OUT)
led = Pin("LED", Pin.OUT)

relay_state = 0
relay.value(relay_state)

last_trigger = time.ticks_ms()

# Optional: require the signal to go LOW before allowing another trigger
armed = True

while True:
    v = sound.value()

    # re-arm once it goes quiet again
    if v == 0:
        armed = True

    now = time.ticks_ms()

    if v == 1 and armed and time.ticks_diff(now, last_trigger) > COOLDOWN_MS:
        relay_state = 0 if relay_state else 1
        relay.value(relay_state)

        led.toggle()
        print("RELAY:", "ON" if relay_state else "OFF")

        last_trigger = now
        armed = False  # wait for silence before next trigger

    time.sleep(0.01)
