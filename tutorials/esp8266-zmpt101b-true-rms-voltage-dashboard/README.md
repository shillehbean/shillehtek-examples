# ESP8266 ZMPT101B: True RMS AC Voltage Dashboard

This tutorial builds an ESP8266-based true-RMS AC voltmeter using the ZMPT101B single-phase voltage sensor and publishes live calibrated voltage readings. The provided sketch samples the sensor, computes RMS using a running-statistics filter, applies a user-set calibration (intercept and slope), and prints the voltage to Serial for use with an MQTT/dashboard setup.

**Read the full tutorial:** [ESP8266 ZMPT101B: True RMS AC Voltage Dashboard](https://shillehtek.com/blogs/news/esp8266-zmpt101b-true-rms-voltage-dashboard)  
**Parts used:** [ZMPT101B AC Single-Phase Voltage Sensor Module](https://shillehtek.com/products/ac-voltage-sensor-zmpt101b-arduino-esp32-raspberry-pi) · [ESP8266 D1 Mini V3 Pre-Soldered](https://shillehtek.com/products/esp8266-d1-mini-v3-4mb-dev-board-presoldered) · [MB102 Breadboard Power Supply (3.3V/5V)](https://shillehtek.com/products/shillehtek-universal-power-supply-module) · [TP4056 LiPo Charging Board](https://shillehtek.com/products/18650-tp4056-1a-3-7-4-2v-lipo-battery-charging-board-micro-usb-with-current-protection) · [830-Point Breadboard](https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)

![ESP8266 ZMPT101B: True RMS AC Voltage Dashboard](https://cdn.shopify.com/s/files/1/0837/4340/8415/articles/blog-thumbnail-630222881055.png?v=1787360849)

## Examples in this folder

- [`esp32/`](./esp32/) — 1 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/esp8266-zmpt101b-true-rms-voltage-dashboard](https://shillehtek.com/blogs/news/esp8266-zmpt101b-true-rms-voltage-dashboard). Last verified: see commit history._
