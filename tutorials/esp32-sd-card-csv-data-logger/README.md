# ESP32 SD Card: Local CSV Data Logging Setup

This tutorial shows how to set up an ESP32-based CSV data logger that writes sensor readings to a microSD card, with an optional DS3231 RTC for timestamping. The code examples include basic DHT22 logging, adding RTC timestamps, creating daily log filenames, and an example of faster buffered logging with periodic flushes.

**Read the full tutorial:** [ESP32 SD Card: Local CSV Data Logging Setup](https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger)  
**Parts used:** [ESP-WROOM-32 (ESP-32S) ESP32 Dev Board CP2102 USB-C Pre-Soldered](https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered) · [XIAO ESP32S3 Pre-Soldered Microcontroller with WiFi & Bluetooth for Arduino & MicroPython](https://shillehtek.com/products/xiao-seeed-esp32s3-pre-soldered-with-usb-c-cable) · [DHT22 Temperature & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-dht22-with-cables) · [BME280 Pre-Soldered Temperature, Pressure & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor) · [DS18B20 Waterproof Digital Temperature Sensor Probe 1M for Arduino & Raspberry Pi](https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi) · [Micro SD TF Card Adapter Reader Module SPI Interface for Arduino](https://shillehtek.com/products/micro-sd-tf-card-adapter-reader-module-spi-interface-for-arduino) · [DS3231 AT24C32 Precision RTC I2C Module with CR2032 Battery](https://shillehtek.com/products/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery)

![ESP32 SD Card: Local CSV Data Logging Setup](https://shillehtek.com/cdn/shop/articles/blog-thumbnail-628631601439_924a20f4-a94c-4586-a02c-1e5f5260f27e.png?v=1783659900)

## Examples in this folder

- [`esp32/`](./esp32/) — 4 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger](https://shillehtek.com/blogs/news/esp32-sd-card-csv-data-logger). Last verified: see commit history._
