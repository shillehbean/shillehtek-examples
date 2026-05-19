# Output a 440 Hz PWM square wave on GP15 (MicroPython) to produce an A4 tone through an RC low-pass filter, run for 2 seconds, then stop.
#
# Buy this module: https://shillehtek.com/products/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-pre-soldered-3-5mm-stereo-audio-jack-breakout-board-manual
# More examples: https://github.com/shillehtek/examples
#

# Play a 440 Hz tone out the audio jack via PWM (with RC low-pass filter)
# Wire: GP15 -> 1k resistor -> TIP, then 10nF capacitor TIP -> SLEEVE (GND)

from machine import Pin, PWM
import time

audio = PWM(Pin(15))
audio.freq(440)         # A4 tone
audio.duty_u16(32768)   # 50% duty -> square wave at 440 Hz

time.sleep(2)

audio.deinit()
