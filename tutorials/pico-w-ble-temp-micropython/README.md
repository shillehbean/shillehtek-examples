# Raspberry Pi Pico W BLE: Temp in MicroPython

This tutorial demonstrates building a BLE peripheral and a BLE central on a Raspberry Pi Pico W using MicroPython and aioble to stream and read the on-board temperature. The peripheral exposes the Ambient Temperature characteristic from the Environmental Sensing service and updates it from the Pico's internal temperature sensor. The central scans for the peripheral, connects, and decodes the temperature characteristic for display or validation (for example with nRF Connect).

**Read the full tutorial:** [Raspberry Pi Pico W BLE: Temp in MicroPython](https://shillehtek.com/blogs/news/pico-w-ble-temp-micropython)  
**Parts used:** [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)

![Raspberry Pi Pico W BLE: Temp in MicroPython](https://shillehtek.com/cdn/shop/articles/blog-thumbnail-625949704479.png?v=1782434622)

## Examples in this folder

- [`micropython/`](./micropython/) — 2 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/pico-w-ble-temp-micropython](https://shillehtek.com/blogs/news/pico-w-ble-temp-micropython). Last verified: see commit history._
