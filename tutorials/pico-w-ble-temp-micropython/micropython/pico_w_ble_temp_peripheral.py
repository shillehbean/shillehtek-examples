# Defines a BLE GATT peripheral that exposes the Environmental Sensing temperature characteristic, encodes the Pico W on-board temperature, and updates the characteristic for read/notify.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-ble-temp-micropython
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# Based on the Random Nerd Tutorials BLE example for the Raspberry Pi Pico W
# Project reference: https://RandomNerdTutorials.com/raspberry-pi-pico-w-bluetooth-low-energy-micropython/

from micropython import const
import asyncio
import aioble
import bluetooth
import struct
from picozero import pico_temp_sensor

# org.bluetooth.service.environmental_sensing
_ENV_SENSE_UUID = bluetooth.UUID(0x181A)
# org.bluetooth.characteristic.temperature
_ENV_SENSE_TEMP_UUID = bluetooth.UUID(0x2A6E)
# org.bluetooth.characteristic.gap.appearance.xml
_ADV_APPEARANCE_GENERIC_THERMOMETER = const(768)

# How frequently to send advertising beacons.
_ADV_INTERVAL_MS = 250_000

# Register GATT server.
temp_service = aioble.Service(_ENV_SENSE_UUID)
temp_characteristic = aioble.Characteristic(
    temp_service, _ENV_SENSE_TEMP_UUID, read=True, notify=True
)
aioble.register_services(temp_service)

# Encode the temperature characteristic value (sint16, hundredths of a degree).
def _encode_temperature(temp_deg_c):
    return struct.pack("<h", int(temp_deg_c * 100))

# Read the on-board temperature and update the characteristic.
async def sensor_task():
    while True:
        temperature = pico_temp_sensor.temp
        temp_characteristic.write(_encode_temperature(temperature), send_update=True)
        print(temperature)
        await asyncio.sleep_ms(1000)

# Advertise the service. Pause advertising while a central is connected.
async def peripheral_task():
    while True:
        try:
            async with await aioble.advertise(
                _ADV_INTERVAL_MS,
                name="RPi-Pico",
                services=[_ENV_SENSE_UUID],
                appearance=_ADV_APPEARANCE_GENERIC_THERMOMETER,
            ) as connection:
                print("Connection from", connection.device)
                await connection.disconnected()
        except asyncio.CancelledError:
            print("Peripheral task cancelled")
        except Exception as e:
            print("Error in peripheral_task:", e)
        finally:
            await asyncio.sleep_ms(100)

# Run both tasks.
async def main():
    t1 = asyncio.create_task(sensor_task())
    t2 = asyncio.create_task(peripheral_task())
    await asyncio.gather(t1, t2)

asyncio.run(main())
