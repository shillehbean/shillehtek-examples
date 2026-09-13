# Arduino examples

- [`lcd_pins.ino`](./lcd_pins.ino) — Instantiates a LiquidCrystal object using Arduino pins 7, 6, 5, 4, 3 and 2 for a 16x2 LCD.
- [`rf_lcd_receiver.ino`](./rf_lcd_receiver.ino) — RF receiver sketch using the VirtualWire library to receive messages and display the received text on a 16x2 LiquidCrystal LCD.
- [`rf_serial_transmitter.ino`](./rf_serial_transmitter.ino) — RF transmitter sketch that reads characters from Serial until a '.' terminator and sends the collected string via VirtualWire.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-433mhz-rf-send-text-lcd)  
Parts used: [433MHz RF Wireless Transmitter & Receiver Link Kit for Arduino](https://shillehtek.com/products/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino) · [LCD1602 16x2 LCD Display Module for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [830 Point Solderless Breadboard for Arduino, Raspberry Pi & ESP32](https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers)
