# Raspberry Pi (gpiozero) example that uses a MotionSensor on GPIO17, registers callbacks for motion/no-motion events, and blocks with pause() after warming up.
#
# Buy this module: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr501-pir-motion-sensor
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# HC-SR501 PIR Motion Sensor on Raspberry Pi
# Install: pip install gpiozero

from gpiozero import MotionSensor
from signal import pause

pir = MotionSensor(17)

print("PIR warming up...")
pir.wait_for_no_motion()
print("Ready. Waiting for motion.")

pir.when_motion    = lambda: print("Motion detected!")
pir.when_no_motion = lambda: print("All clear.")

pause()
