# MicroPython script for a Raspberry Pi Pico W that drives two DC motors via an L298N using PWM, with functions for forward, backward, left, right, stop and a percent-to-duty converter.
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-l298n-program-robot-movements
# Parts used: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

"""
This program controls two DC motors using PWM on a Raspberry Pi Pico. 
It allows the user to set a speed (0-100%) and moves the motors forward, backward, 
left, and right in a loop. If the motors move in the wrong direction, 
reverse their polarity by swapping the connections on the respective DC motor.
"""


from machine import Pin, PWM
from time import sleep

# ───── Helper function to convert 0–100% into duty_u16 value (0–65535) ─────
def percent_to_duty(percentage):
    # Clamp the percentage between 0 and 100
    if percentage < 0:
        percentage = 0
    elif percentage > 100:
        percentage = 100
    return int((65535 * percentage) / 100)

# ───── MOTOR B (Existing) ─────
in3 = Pin(2, Pin.OUT)   # GPIO2
in4 = Pin(3, Pin.OUT)   # GPIO3
enb = PWM(Pin(9))       # GPIO9 for PWM
enb.freq(1000)          # Set PWM frequency to 1 kHz (reduces audible noise, balances efficiency)

def motorB_forward(duty):
    in3.high()
    in4.low()
    enb.duty_u16(duty)

def motorB_backward(duty):
    in3.low()
    in4.high()
    enb.duty_u16(duty)

def motorB_stop():
    in3.low()
    in4.low()
    enb.duty_u16(0)

# ───── MOTOR A (New) ─────
in1 = Pin(0, Pin.OUT)   # GPIO0
in2 = Pin(1, Pin.OUT)   # GPIO1
ena = PWM(Pin(8))       # GPIO8 for PWM
ena.freq(1000)          # Set PWM frequency to 1 kHz

def motorA_forward(duty):
    in1.high()
    in2.low()
    ena.duty_u16(duty)

def motorA_backward(duty):
    in1.low()
    in2.high()
    ena.duty_u16(duty)

def motorA_stop():
    in1.low()
    in2.low()
    ena.duty_u16(0)

# ───── MAIN LOOP ─────
try:
    while True:
        # Ask the user for a speed percentage
        user_input = input("Enter speed (0–100) for both motors (Ctrl-C to quit): ")
        if not user_input.isdigit():
            print("Please enter a valid integer between 0 and 100!")
            continue

        speed_percent = int(user_input)
        # Convert percentage to duty cycle (0–65535)
        duty_value = percent_to_duty(speed_percent)

        # 1. Move FORWARD at user-specified speed
        print(f"Moving both motors FORWARD at {speed_percent}%")
        motorA_forward(duty_value)
        motorB_forward(duty_value)
        sleep(2)

        # Stop motors
        print("Stopping motors...")
        motorA_stop()
        motorB_stop()
        sleep(1)

        # 2. Move BACKWARD at user-specified speed
        print(f"Moving both motors BACKWARD at {speed_percent}%")
        motorA_backward(duty_value)
        motorB_backward(duty_value)
        sleep(2)

        # Stop motors
        print("Stopping motors...")
        motorA_stop()
        motorB_stop()
        sleep(1)

        # 3. Turn LEFT
        #    (Motor A backward, Motor B forward)
        print(f"Turning LEFT at {speed_percent}%")
        motorA_backward(duty_value)
        motorB_forward(duty_value)
        sleep(2)

        # Stop motors
        print("Stopping motors...")
        motorA_stop()
        motorB_stop()
        sleep(1)

        # 4. Turn RIGHT
        #    (Motor A forward, Motor B backward)
        print(f"Turning RIGHT at {speed_percent}%")
        motorA_forward(duty_value)
        motorB_backward(duty_value)
        sleep(2)

        # Stop motors
        print("Stopping motors...")
        motorA_stop()
        motorB_stop()
        sleep(1)

except KeyboardInterrupt:
    motorA_stop()
    motorB_stop()
    print("\nProgram stopped by user.")
