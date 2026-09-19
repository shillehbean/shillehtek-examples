# Plays a simple melody on a Raspberry Pi Pico using PWM on GP15 to produce square-wave tones into the PAM8406 input (via resistor/coupling cap).
#
# Buy this module: https://shillehtek.com/products/pam8406-stereo-class-d-amplifier-module-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pam8406-stereo-class-d-amplifier-module-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# PAM8406 Amplifier - Pico MicroPython Example (PWM melody)
# GP15 -> 1k -> INL, INL -> 100nF -> GND, speaker across +L/-L

from machine import Pin, PWM
import time

spk = PWM(Pin(15))

MELODY = [
    (262, 200), (330, 200), (392, 200), (523, 400),
    (392, 200), (523, 600),
]

def play(freq, ms):
    spk.freq(freq)
    spk.duty_u16(32768)       # 50% duty = loudest square tone
    time.sleep_ms(ms)
    spk.duty_u16(0)           # silence between notes
    time.sleep_ms(30)

print("Playing jingle on PAM8406...")
while True:
    for freq, ms in MELODY:
        play(freq, ms)
    time.sleep(2)
