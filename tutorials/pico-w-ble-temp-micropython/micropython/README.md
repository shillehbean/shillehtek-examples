# Micropython examples

- [`pico_w_ble_temp_peripheral.py`](./pico_w_ble_temp_peripheral.py) — Defines a BLE GATT peripheral that exposes the Environmental Sensing temperature characteristic, encodes the Pico W on-board temperature, and updates the characteristic for read/notify.
- [`pico_w_ble_temp_central.py`](./pico_w_ble_temp_central.py) — Implements a BLE central that scans for a peripheral named 'RPi-Pico', connects, and decodes the Environmental Sensing temperature characteristic (sint16, hundredths of a degree).

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/pico-w-ble-temp-micropython)  
Parts used: [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
