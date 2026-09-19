# Sends a raw Modbus-RTU request from a Raspberry Pi serial port to read PZEM-004T registers, decodes voltage/current/power/energy/frequency/pf and prints the results.
#
# Buy this module: https://shillehtek.com/products/pzem-004t-ac-energy-meter-current-transformer
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pzem-004t-ac-energy-meter-current-transformer-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# PZEM-004T V3 - Raspberry Pi Example (raw Modbus-RTU)
# TX->GPIO15, RX->GPIO14 (or use /dev/ttyUSB0)
# Install: pip3 install pyserial

import serial, struct, time

def crc16(data):
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 1:
                crc = (crc >> 1) ^ 0xA001
            else:
                crc >>= 1
    return crc

port = serial.Serial("/dev/serial0", 9600, timeout=1)

# Read 10 input registers from address 0xF8
request = bytes([0xF8, 0x04, 0x00, 0x00, 0x00, 0x0A])
request += struct.pack("<H", crc16(request))

while True:
    port.write(request)
    resp = port.read(25)
    if len(resp) == 25:
        regs = struct.unpack(">10H", resp[3:23])
        voltage = regs[0] / 10
        current = (regs[1] + (regs[2] << 16)) / 1000
        power   = (regs[3] + (regs[4] << 16)) / 10
        energy  = (regs[5] + (regs[6] << 16)) / 1000
        freq    = regs[7] / 10
        pf      = regs[8] / 100
        print(f"{voltage:.1f} V  {current:.3f} A  {power:.1f} W  "
              f"{energy:.3f} kWh  {freq:.1f} Hz  PF {pf:.2f}")
    else:
        print("No/short response - check wiring and mains")
    time.sleep(1)
