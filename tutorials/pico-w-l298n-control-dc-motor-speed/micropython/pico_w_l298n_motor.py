# Configures Pico W GPIO and PWM to drive a DC motor via the L298N, providing functions to move forward, backward, and stop, and runs a simple test loop toggling direction and stopping.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-l298n-control-dc-motor-speed
# Parts used: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

from machine import Pin, PWM
from time import sleep

# Motor pins
in3 = Pin(14, Pin.OUT)  # IN3 connected to GPIO 14
in4 = Pin(15, Pin.OUT)  # IN4 connected to GPIO 15
enb = PWM(Pin(13))      # ENB connected to GPIO 13 for PWM control
enb.freq(1000)          # Set PWM frequency to 1 kHz

# Motor functions
def motor_forward(speed):
    in3.high()          # Set IN3 high
    in4.low()           # Set IN4 low
    enb.duty_u16(speed) # Set motor speed (0-65535 for duty cycle)

def motor_backward(speed):
    in3.low()           # Set IN3 low
    in4.high()          # Set IN4 high
    enb.duty_u16(speed) # Set motor speed (0-65535 for duty cycle)

def motor_stop():
    in3.low()           # Stop motor
    in4.low()           # Stop motor
    enb.duty_u16(0)     # Disable motor (set PWM duty cycle to 0)

# Main loop to test motor
try:
    while True:
        print("Moving forward")
        motor_forward(32768)  # Set speed to 50% (PWM value)
        sleep(2)

        print("Stopping")
        motor_stop()
        sleep(2)

        print("Moving backward")
        motor_backward(32768)  # Set speed to 50% (PWM value)
        sleep(2)

        print("Stopping")
        motor_stop()
        sleep(2)
except KeyboardInterrupt:
    motor_stop()
    print("Program stopped")
