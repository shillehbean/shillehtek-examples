# Controls two servos on a Raspberry Pi using gpiozero with pigpio backend, performing smooth glide movements for pan and tilt patrols.
#
# Buy this module: https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pan-tilt-servo-bracket-kit-sg90-mg90s-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from gpiozero import AngularServo
from gpiozero.pins.pigpio import PiGPIOFactory
from time import sleep

# sudo apt install pigpio; sudo systemctl start pigpiod
factory = PiGPIOFactory()

def servo(pin):
    return AngularServo(pin, min_angle=0, max_angle=180,
                        min_pulse_width=0.0005, max_pulse_width=0.0025,
                        pin_factory=factory)

pan, tilt = servo(17), servo(27)
pan.angle, tilt.angle = 90, 90
sleep(1)

def glide(s, start, end, step=2, dt=0.02):
    rng = range(start, end + 1, step) if end > start else range(start, end - 1, -step)
    for a in rng:
        s.angle = a
        sleep(dt)

while True:
    glide(pan, 90, 30)
    glide(pan, 30, 150)
    glide(pan, 150, 90)
    glide(tilt, 90, 65)
    glide(tilt, 65, 115)
    glide(tilt, 115, 90)
    sleep(1)
