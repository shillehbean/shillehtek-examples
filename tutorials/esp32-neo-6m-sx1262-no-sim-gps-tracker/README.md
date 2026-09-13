# ESP32-S3 NEO-6M: No-SIM LoRa GPS Tracker

This project implements an off-grid GPS tracker using an ESP32-S3, a NEO-6M GPS module, and an SX1262 LoRa radio to send live coordinates to a base station. The code folder contains two Arduino-framework sketches: a transmitter that reads GPS NMEA, parses latitude/longitude, and sends them over LoRa, and a receiver that listens for LoRa packets and prints received coordinates to the serial console.

**Read the full tutorial:** [ESP32-S3 NEO-6M: No-SIM LoRa GPS Tracker](https://shillehtek.com/blogs/news/esp32-neo-6m-sx1262-no-sim-gps-tracker)  
**Parts used:** [GT-U7 NEO-6M GPS Module Pre-Soldered for Arduino & Raspberry Pi](https://shillehtek.com/products/gt-u7-gps-module-presoldered-1) · [SX1262 ESP32-S3 0.96" Blue OLED Bluetooth & WiFi Development Board for Arduino, 868-915MHz, with Antenna, Pre-Soldered](https://shillehtek.com/products/sx1262-esp32-s3-0-96-inch-blue-oled-display-bluetooth-wifi-kit-32-module-iot-development-board-for-arduino-w-antenna-868-915mhz-with-soldering-and-foam) · [TP4056 1A 3.7-4.2V LiPo Battery Charging Board with Micro USB & Current Protection](https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection) · [120pcs 20cm Dupont Jumper Wires for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire) · [ADXL345 Pre-Soldered Accelerometer Sensor for Arduino, Raspberry Pi & Klipper](https://shillehtek.com/products/shillehtek-adxl345-pre-soldered)

![ESP32-S3 NEO-6M: No-SIM LoRa GPS Tracker](https://shillehtek.com/cdn/shop/articles/blog-thumbnail-626596938015.png?v=1779638144)

## Examples in this folder

- [`esp32/`](./esp32/) — 2 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/esp32-neo-6m-sx1262-no-sim-gps-tracker](https://shillehtek.com/blogs/news/esp32-neo-6m-sx1262-no-sim-gps-tracker). Last verified: see commit history._
