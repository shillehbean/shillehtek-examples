# Uses gpiozero's TonalBuzzer on a Raspberry Pi (GPIO 18) to play a short sequence of musical notes (C4, E4, G4, C5).
#
# Buy this module: https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects-manual
# More examples: https://github.com/shillehtek/examples
#

#!/usr/bin/env python3
# KY-006 on Raspberry Pi - play a tone with gpiozero
# pip install gpiozero

from gpiozero import TonalBuzzer
from gpiozero.tones import Tone
import time

buzzer = TonalBuzzer(18)        # GPIO 18 (hardware PWM)

for note in ["C4", "E4", "G4", "C5"]:
    buzzer.play(Tone(note))
    time.sleep(0.4)

buzzer.stop()
