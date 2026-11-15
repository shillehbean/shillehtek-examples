# Raspberry Pi Python script using smbus2 to trigger a measurement on the SHT45, read the 6-byte reply, verify CRC, and compute temperature (°C) and humidity (%RH).
#
# Buy this module: https://shillehtek.com/products/sht45-i2c-temperature-humidity-sensor-module-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sht45-i2c-temperature-humidity-sensor-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# GY-SHT45 temperature and humidity on Raspberry Pi (I2C bus 1)
# Install once: sudo apt install python3-smbus2   (enable I2C in raspi-config)
import time
from smbus2 import SMBus, i2c_msg

SHT45_ADDR = 0x44
CMD_MEASURE_HIGH = 0xFD     # high precision, heater off


def crc8(data):
    """CRC-8 used by the SHT4x: polynomial 0x31, start value 0xFF."""
    crc = 0xFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            crc = ((crc << 1) ^ 0x31) & 0xFF if crc & 0x80 else (crc << 1) & 0xFF
    return crc


def read_sht45(bus):
    bus.i2c_rdwr(i2c_msg.write(SHT45_ADDR, [CMD_MEASURE_HIGH]))
    time.sleep(0.01)                            # a conversion takes up to 8.3 ms
    reply = i2c_msg.read(SHT45_ADDR, 6)
    bus.i2c_rdwr(reply)
    data = list(reply)
    if crc8(data[0:2]) != data[2] or crc8(data[3:5]) != data[5]:
        raise ValueError("Checksum mismatch - check the wiring")
    raw_t = (data[0] << 8) | data[1]
    raw_rh = (data[3] << 8) | data[4]
    temp_c = -45 + 175 * raw_t / 65535
    humidity = min(100.0, max(0.0, -6 + 125 * raw_rh / 65535))
    return temp_c, humidity


with SMBus(1) as bus:
    while True:
        temp_c, humidity = read_sht45(bus)
        print(f"Temperature: {temp_c:.2f} C   Humidity: {humidity:.1f} %RH")
        time.sleep(2)
