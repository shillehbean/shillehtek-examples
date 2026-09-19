# MicroPython example for the RP2040 Pico demonstrating AT-mode configuration via the SET pin and continuous transparent-mode transmit/receive over UART0.
#
# Buy this module: https://shillehtek.com/products/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# HC-12 - Pico MicroPython Example with AT config
# TXD->GP1, RXD->GP0, SET->GP2

from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1), timeout=300)
set_pin = Pin(2, Pin.OUT, value=1)      # HIGH = transparent mode

def at(cmd):
    """Send one AT command with SET low, return the reply."""
    set_pin.value(0)
    time.sleep_ms(50)
    uart.write(cmd + "\r\n")
    time.sleep_ms(150)
    reply = uart.read()
    set_pin.value(1)
    time.sleep_ms(80)
    return reply.decode(errors="ignore").strip() if reply else "(no reply)"

# One-time setup: channel 5, full power, confirm firmware
print("AT      :", at("AT"))          # expect OK
print("Channel :", at("AT+C005"))    # both ends must match!
print("Power   :", at("AT+P8"))      # +20 dBm
print("Version :", at("AT+V"))

counter = 0
while True:
    uart.write("PICO,{}\n".format(counter))
    print("sent PICO,{}".format(counter))
    counter += 1

    data = uart.read()
    if data:
        print("recv:", data.decode(errors="ignore").strip())
    time.sleep(1)
