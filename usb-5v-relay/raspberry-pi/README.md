# Raspberry Pi examples

- [`example_1.py`](./example_1.py) — Minimal Linux command-line (bash) script that sets the serial port parameters and writes the 4-byte ON or OFF sequence to a USB serial device for quick on/off control.
- [`example_2.py`](./example_2.py) — Node.js example using the serialport package to open the USB serial device, write the ON command, wait 2 seconds, then write the OFF command and close the port.
- [`example_3.py`](./example_3.py) — Raspberry Pi Python example (pyserial) that pulses the relay ON for 5 seconds by writing the ON command to /dev/ttyUSB0, then writes the OFF command and closes the port.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/usb-control-module-1-channel-5v-relay-module-no-driver-needed-manual)  
Buy the module: https://shillehtek.com/products/usb-control-module-1-channel-5v-relay-module-no-driver-needed
