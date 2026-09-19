# MicroPython example for the Pico using UART(0) and a direction pin (GP2) to send newline‑terminated messages over RS‑485, then switch back to receive and print any responses.
#
# Buy this module: https://shillehtek.com/products/max485-ttl-rs485-converter-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max485-ttl-rs485-converter-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# MAX485 RS-485 - Pico MicroPython Example
# RO->GP1, DI->GP0, RE+DE->GP2

from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1))
dir_pin = Pin(2, Pin.OUT, value=0)     # 0 = receive

def send(msg):
    dir_pin.value(1)
    time.sleep_us(100)
    uart.write(msg + "\n")
    # wait for the frame to leave the shift register
    time.sleep_ms(2 + len(msg))
    dir_pin.value(0)

counter = 0
print("RS-485 node ready")
while True:
    send("PICO MSG {}".format(counter))
    counter += 1

    t0 = time.ticks_ms()
    while time.ticks_diff(time.ticks_ms(), t0) < 1000:
        if uart.any():
            line = uart.readline()
            if line:
                print("Received:", line.decode().strip())
