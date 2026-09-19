# Runs on a Pico with MicroPython to send raw load-record frames over UART, continuously read incoming frames, and print the recognized record number when a voice command is detected.
#
# Buy this module: https://shillehtek.com/products/arduino-voice-recognition-module-v3
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/arduino-voice-recognition-module-v3-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Voice Recognition Module V3 - Pico MicroPython Example (raw protocol)
# Module TXD -> GP1 via divider, Module RXD -> GP0, VCC -> VBUS
# Train the records first with an Arduino - they stay on the module.

from machine import UART, Pin
import time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1), timeout=100)

def load_record(rec):
    # Frame: AA | LEN | 30 (load) | record | 0A
    uart.write(bytes([0xAA, 0x02, 0x30, rec, 0x0A]))
    time.sleep_ms(50)

# Load trained records 0-2 into the active recognizer
for r in (0, 1, 2):
    load_record(r)

print("Speak one of your trained commands...")

buffer = bytearray()

while True:
    data = uart.read()
    if data:
        buffer.extend(data)

        # Complete frames start with 0xAA and end with 0x0A
        while 0xAA in buffer:
            start = buffer.index(0xAA)
            end = buffer.find(b'\n', start)   # 0x0A terminator
            if end < 0:
                break
            frame = buffer[start:end + 1]
            del buffer[:end + 1]

            # frame[2] == 0x0D means "voice recognized";
            # frame[4] holds the record number
            if len(frame) > 5 and frame[2] == 0x0D:
                print("Recognized record #", frame[4])
    time.sleep_ms(20)
