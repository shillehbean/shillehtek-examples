# Runs on a Raspberry Pi Pico (MicroPython) to send a Modbus-RTU read request to the PZEM-004T over UART, parse returned registers, and print voltage, current, power and energy periodically.
#
# Buy this module: https://shillehtek.com/products/pzem-004t-ac-energy-meter-current-transformer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pzem-004t-ac-energy-meter-current-transformer-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# PZEM-004T V3 - Pico MicroPython Example (raw Modbus-RTU)
# TX->GP1, RX->GP0, 5V->VBUS

from machine import UART, Pin
import struct, time

uart = UART(0, baudrate=9600, tx=Pin(0), rx=Pin(1), timeout=300)

def crc16(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            crc = (crc >> 1) ^ 0xA001 if crc & 1 else crc >> 1
    return crc

req = bytes([0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A])
req += struct.pack("<H", crc16(req))

while True:
    uart.write(req)
    time.sleep_ms(200)
    resp = uart.read()
    if resp and len(resp) >= 25:
        regs = struct.unpack(">10H", resp[3:23])
        voltage = regs[0] / 10
        current = (regs[1] + (regs[2] << 16)) / 1000
        power   = (regs[3] + (regs[4] << 16)) / 10
        energy  = (regs[5] + (regs[6] << 16)) / 1000
        print("{:.1f} V  {:.3f} A  {:.1f} W  {:.3f} kWh".format(
            voltage, current, power, energy))
    else:
        print("No response - check wiring and mains")
    time.sleep(1)
