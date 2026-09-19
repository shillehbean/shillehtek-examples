# Run on a MicroPython board to output 50 Hz PWM for three servos, converting microsecond pulse widths to duty_u16 and performing incremental glide moves between poses.
#
# Buy this module: https://shillehtek.com/products/3dof-robot-arm-kit-mg995-servos
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/3dof-robot-arm-kit-mg995-servos-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
import time

PINS = (13, 14, 15)      # base, shoulder, elbow
servos = []
for p in PINS:
    pwm = PWM(Pin(p))
    pwm.freq(50)
    servos.append(pwm)

def write_us(pwm, us):
    pwm.duty_u16(int(us * 65535 / 20000))

pose = [1500, 1500, 1500]
for s, us in zip(servos, pose):
    write_us(s, us)
time.sleep(1)

def move_to(target, step=6, dt=0.01):
    while pose != list(target):
        for i in range(3):
            if pose[i] < target[i]: pose[i] = min(pose[i] + step, target[i])
            elif pose[i] > target[i]: pose[i] = max(pose[i] - step, target[i])
            write_us(servos[i], pose[i])
        time.sleep(dt)

while True:
    move_to((1250, 1750, 1300))
    time.sleep(0.5)
    move_to((1750, 1350, 1700))
    time.sleep(0.5)
    move_to((1500, 1500, 1500))
    time.sleep(1)
