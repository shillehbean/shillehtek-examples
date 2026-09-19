# Use a Raspberry Pi with pigpio-backed gpiozero AngularServo objects to produce hardware-timed PWM for three servos and execute smooth pose transitions.
#
# Buy this module: https://shillehtek.com/products/3dof-robot-arm-kit-mg995-servos
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3dof-robot-arm-kit-mg995-servos-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from gpiozero import AngularServo
from gpiozero.pins.pigpio import PiGPIOFactory
from time import sleep

# sudo apt install pigpio; sudo systemctl start pigpiod
# pigpio gives hardware-timed pulses = no servo jitter
factory = PiGPIOFactory()

def make(pin):
    return AngularServo(pin, min_angle=0, max_angle=180,
                        min_pulse_width=0.0005, max_pulse_width=0.0025,
                        pin_factory=factory)

base, shoulder, elbow = make(17), make(27), make(22)

def glide(servo, start, end, step=2, dt=0.02):
    rng = range(start, end + 1, step) if end > start else range(start, end - 1, -step)
    for a in rng:
        servo.angle = a
        sleep(dt)

# center, then run a small routine
for s in (base, shoulder, elbow):
    s.angle = 90
sleep(1)

while True:
    glide(base, 90, 45)
    glide(shoulder, 90, 125)
    glide(elbow, 90, 60)
    sleep(0.5)
    glide(elbow, 60, 90)
    glide(shoulder, 125, 90)
    glide(base, 45, 90)
    sleep(1)
