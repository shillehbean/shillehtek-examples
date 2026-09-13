# Arduino examples

- [`joystick_serial_monitor.ino`](./joystick_serial_monitor.ino) — Reads X/Y analog axes and seven digital buttons from the joystick shield and prints their values to the serial monitor.
- [`axis_read_helpers.ino`](./axis_read_helpers.ino) — Provides a helper function that normalizes an analog axis reading to a -100..100 range with a configurable deadzone and mapping based on min/center/max values.
- [`joystick_usb_hid.ino`](./joystick_usb_hid.ino) — Publishes the joystick axes and buttons as a USB HID gamepad using the Joystick library (for ATmega32U4-based boards like Pro Micro).
- [`joystick_nrf24_transmitter.ino`](./joystick_nrf24_transmitter.ino) — Reads the joystick axes and buttons and transmits the packed state over an nRF24L01+ radio as a simple wireless gamepad packet.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-uno-joystick-shield-usb-gamepad-nrf24-transmitter)  
Parts used: [Joystick Shield V1.A 2-Axis Analog Gamepad Controller for Arduino UNO R3](https://shillehtek.com/products/joystick-shield-v1-a-gamepad-controller-module-for-arduino-r3) · [NRF24L01+ 2.4GHz Wireless Transceiver Module SPI for Arduino & Raspberry Pi](https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino) · [Pro Micro ATmega32U4 5V 16MHz Pre-Soldered Micro-USB Development Board](https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb) · [L298N Motor Driver Board for Arduino & Raspberry Pi DC and Stepper Motors](https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board)
