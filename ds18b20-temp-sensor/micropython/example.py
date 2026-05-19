# Runs on MicroPython (e.g., Raspberry Pi Pico), scans for DS18B20 devices on a OneWire pin, triggers conversion, and reads/prints each sensor's Celsius temperature.
#
# Buy this module: https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi-manual
# More examples: https://github.com/shillehtek/examples
#

# DS18B20 on Raspberry Pi Pico (MicroPython)
# Wire: Red=3V3, Black=GND, Yellow=GP15 with 4.7k pull-up to 3V3

from machine import Pin
import onewire, ds18x20, time

ow = onewire.OneWire(Pin(15))
ds = ds18x20.DS18X20(ow)

roms = ds.scan()
print("Found", len(roms), "DS18B20 sensors")

while True:
    ds.convert_temp()
    time.sleep_ms(750)
    for rom in roms:
        c = ds.read_temp(rom)
        print("{}: {:.2f} C".format(bytes(rom).hex(), c))
    time.sleep(1)
