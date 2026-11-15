# MicroPython example for Raspberry Pi Pico that talks to the SHT45 over I2C, checks CRC-8 on the returned data, and converts raw sensor values into temperature and humidity readings.
#
# Buy this module: https://shillehtek.com/products/sht45-i2c-temperature-humidity-sensor-module-pre-soldered
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sht45-i2c-temperature-humidity-sensor-module-pre-soldered-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# GY-SHT45 temperature and humidity on Raspberry Pi Pico (MicroPython)
# SDA = GP4 (pin 6), SCL = GP5 (pin 7), VIN = 3V3(OUT), GND = GND
from machine import I2C, Pin
import time

SHT45_ADDR = 0x44
CMD_MEASURE_HIGH = 0xFD     # high precision, heater off

i2c = I2C(0, sda=Pin(4), scl=Pin(5), freq=100000)
print("I2C scan:", [hex(a) for a in i2c.scan()])   # expect 0x44


def crc8(data):
    # CRC-8 used by the SHT4x: polynomial 0x31, start value 0xFF
    crc = 0xFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x80:
                crc = ((crc << 1) ^ 0x31) & 0xFF
            else:
                crc = (crc << 1) & 0xFF
    return crc


def read_sht45():
    i2c.writeto(SHT45_ADDR, bytes([CMD_MEASURE_HIGH]))
    time.sleep_ms(10)                           # a conversion takes up to 8.3 ms
    data = i2c.readfrom(SHT45_ADDR, 6)
    if crc8(data[0:2]) != data[2] or crc8(data[3:5]) != data[5]:
        raise ValueError("Checksum mismatch - check the wiring")
    raw_t = (data[0] << 8) | data[1]
    raw_rh = (data[3] << 8) | data[4]
    temp_c = -45 + 175 * raw_t / 65535
    humidity = min(100, max(0, -6 + 125 * raw_rh / 65535))
    return temp_c, humidity


while True:
    temp_c, humidity = read_sht45()
    print("Temperature: {:.2f} C   Humidity: {:.1f} %RH".format(temp_c, humidity))
    time.sleep(2)
