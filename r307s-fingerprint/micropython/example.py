# MicroPython example for the Pico demonstrating the raw R307S packet protocol over UART: build and send command frames (VfyPwd shown), read acknowledgements, and prepare for continuous fingerprint capture via raw commands.
#
# Buy this module: https://shillehtek.com/products/fingerprint-sensor-r307s-optical-arduino-esp32
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/fingerprint-sensor-r307s-optical-arduino-esp32-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# R307S Fingerprint Sensor - Pico MicroPython Example
# Sensor TXD -> GP1 (UART0 RX), Sensor RXD -> GP0 (UART0 TX), +5V -> VBUS
# Talks the raw protocol - no library needed.

from machine import UART, Pin
import time

uart = UART(0, baudrate=57600, tx=Pin(0), rx=Pin(1), timeout=500)

HEADER = b'\xef\x01'
ADDRESS = b'\xff\xff\xff\xff'

def send_cmd(payload):
    # payload = instruction + parameters (without length/checksum)
    length = len(payload) + 2
    packet = b'\x01' + bytes([length >> 8, length & 0xFF]) + payload
    checksum = sum(packet)
    frame = HEADER + ADDRESS + packet + bytes(
        [(checksum >> 8) & 0xFF, checksum & 0xFF])
    uart.write(frame)

def read_ack():
    time.sleep_ms(100)
    resp = uart.read()
    if resp and len(resp) >= 12 and resp[:2] == HEADER:
        return resp[9]  # confirmation code: 0x00 = success
    return None

# --- Check the sensor answers (VfyPwd with default password 0x00000000)
send_cmd(b'\x13\x00\x00\x00\x00')
if read_ack() == 0x00:
    print('Fingerprint sensor found!')
else:
    raise RuntimeError('Sensor not responding - check wiring and baud')

print('Touch the sensor window...')

while True:
    # GenImg: capture a fingerprint image if a finger is present
    send_cmd(b'\x01')
    code = read_ack()

    if code == 0x00:
        print('Finger detected and image captured!')
        time.sleep(1)   # Debounce so one touch prints once
    # 0x02 means "no finger on the window" - keep polling quietly
    time.sleep_ms(200)
