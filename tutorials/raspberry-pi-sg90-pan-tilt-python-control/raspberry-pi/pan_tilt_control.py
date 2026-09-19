# Move two SG90/MG90S servos on pan and tilt channels to specified angles using RPi.GPIO PWM, then clean up GPIO state.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-sg90-pan-tilt-python-control
# Parts used: https://shillehtek.com/products/pan-tilt-servo-bracket-kit-sg90-mg90s
#             https://shillehtek.com/products/servo-tester-rc-ccpm-checker
#             https://shillehtek.com/products/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from time import sleep
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

pan  = 27
tilt = 17

GPIO.setup(tilt, GPIO.OUT)
GPIO.setup(pan, GPIO.OUT)

def setServoAngle(servo, angle):
    assert 30 <= angle <= 150          # stay inside the mechanical sweet spot
    pwm = GPIO.PWM(servo, 50)          # 50 Hz servo frame
    pwm.start(8)                       # start near center
    dutyCycle = angle / 18. + 3.       # 0-180 deg  ->  3%-13% duty
    pwm.ChangeDutyCycle(dutyCycle)
    sleep(0.3)
    pwm.stop()

# point the head: pan 45 deg, tilt 120 deg
setServoAngle(pan, 45)
setServoAngle(tilt, 120)
GPIO.cleanup()
