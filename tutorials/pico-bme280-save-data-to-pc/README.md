# Raspberry Pi Pico BME280: Save Sensor Data to PC

This tutorial shows how to read temperature, pressure, and humidity from a BME280 sensor attached to a Raspberry Pi Pico and transfer those readings to a local computer over USB serial. The MicroPython script runs on the Pico, reads the BME280 via I2C, and prints measurements to the USB UART. The host Python script listens on the serial port and saves the incoming data to a file on your computer.

**Read the full tutorial:** [Raspberry Pi Pico BME280: Save Sensor Data to PC](https://shillehtek.com/blogs/news/pico-bme280-save-data-to-pc)  
**Parts used:** [BME280 Pre-Soldered Temperature, Pressure & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor) · [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)

![Raspberry Pi Pico BME280: Save Sensor Data to PC](https://shillehtek.com/cdn/shop/articles/blog-thumbnail-606337368351_49184338-bff5-40af-b39d-c98a23e1961a.png?v=1782433775)

## Examples in this folder

- [`micropython/`](./micropython/) — 1 sample(s)
- [`python/`](./python/) — 1 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/pico-bme280-save-data-to-pc](https://shillehtek.com/blogs/news/pico-bme280-save-data-to-pc). Last verified: see commit history._
