# Arduino examples

- [`water_flow_basic.ino`](./water_flow_basic.ino) — Basic sketch that counts pulses from the YF-S201 on D2 and prints the calculated flow in liters per minute to Serial every second.
- [`water_flow_lcd_total.ino`](./water_flow_lcd_total.ino) — Sketch that accumulates total liters over time, calculates L/min, and updates a 16x2 LCD with current flow and total volume (assumes an initialized lcd object).
- [`water_flow_valve_control.ino`](./water_flow_valve_control.ino) — Valve control sketch that uses a relay-controlled valve (active LOW) to stop flow when the accumulated total liters reaches a configured target.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-yf-s201-water-flow-measure-lpm)  
Parts used: [Arduino Nano V3.0 Pre-Soldered CH340G ATmega328P](https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p) · [ESP-WROOM-32 (ESP-32S) ESP32 Dev Board CP2102 USB-C Pre-Soldered](https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered) · [LCD1602 16x2 LCD Display Module for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module) · [1-Channel 12V Relay Module for Arduino & Raspberry Pi](https://shillehtek.com/products/1-channel-12v-relay-module)
