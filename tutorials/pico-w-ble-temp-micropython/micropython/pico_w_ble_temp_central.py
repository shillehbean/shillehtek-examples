# Implements a BLE central that scans for a peripheral named 'RPi-Pico', connects, and decodes the Environmental Sensing temperature characteristic (sint16, hundredths of a degree).
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-ble-temp-micropython
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Based on the Random Nerd Tutorials BLE central device example for the Pico W
# Project reference: https://RandomNerdTutorials.com/raspberry-pi-pico-w-bluetooth-low-energy-micropython/

from micropython import const
import uasyncio as asyncio
import aioble
import bluetooth
import struct

# org.bluetooth.service.environmental_sensing
_ENV_SENSE_UUID = bluetooth.UUID(0x181A)
# org.bluetooth.characteristic.temperature
_ENV_SENSE_TEMP_UUID = bluetooth.UUID(0x2A6E)

# Name of the peripheral you want to connect to.
peripheral_name = "RPi-Pico"

# Decode the temperature characteristic encoding (sint16, hundredths of a degree).
def _decode_temperature(data):
    try:
        if data is not None:
            return struct.unpack("<h", data)[0] / 100
    except Exception as e:
        print("Error decoding temperature:", e)
    return None

async def find_temp_sensor():
    # Active scan for 5 seconds with a tight interval/window for fast detection.
    async with aioble.scan(5000, interval_us=30000, window_us=30000, active=True) as scanner:
        async for result in scanner:
            print(result.name())
            if result.name() == peripheral_name and _ENV_SENSE_UUID in result.services():
                return result.device
    return None

async def main():
    while True:
        device = await find_temp_sensor()
        if not device:
            print("Temperature sensor not found. Retrying...")
            await asyncio.sleep_ms(5000)
            continue

        try:
            print("Connecting to", device)
            connection = await device.connect()
        except asyncio.TimeoutError:
            print("Timeout during connection. Retrying...")
            await asyncio.sleep_ms(5000)
            continue

        async with connection:
            try:
                temp_service = await connection.service(_ENV_SENSE_UUID)
                temp_characteristic = await temp_service.characteristic(_ENV_SENSE_TEMP_UUID)
            except asyncio.TimeoutError:
                print("Timeout discovering services/characteristics. Retrying...")
                await asyncio.sleep_ms(5000)
                continue

            while True:
                try:
                    temp_data = await temp_characteristic.read()
                    if temp_data is not None:
                        temp_deg_c = _decode_temperature(temp_data)
                        if temp_deg_c is not None:
                            print("Temperature: {:.2f}".format(temp_deg_c))
                        else:
                            print("Invalid temperature data")
                    else:
                        print("Error reading temperature: None")
                except Exception as e:
                    print("Error in main loop:", e)
                    break
                await asyncio.sleep_ms(1000)

# Create the event loop and start the main task.
loop = asyncio.get_event_loop()
loop.create_task(main())

try:
    loop.run_forever()
except Exception as e:
    print('Error occurred: ', e)
except KeyboardInterrupt:
    print('Program Interrupted by the user')
