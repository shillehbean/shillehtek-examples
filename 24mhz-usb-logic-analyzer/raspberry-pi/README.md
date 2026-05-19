# Raspberry Pi examples

- [`example_1.py`](./example_1.py) — Basic quick-start steps to use the analyzer with Saleae Logic v1 (legacy): install software, plug in the device, enable protocol analyzers on channels, and start a capture.
- [`example_2.py`](./example_2.py) — Install PulseView and the fx2lafw firmware driver on Linux/macOS/Windows and connect the analyzer in PulseView, then set sample rate and add protocol decoders.
- [`example_3.py`](./example_3.py) — A sigrok-cli command to capture 5 seconds of I2C from channels D0/D1 at 8 MS/s and save the recording as a PulseView-compatible .sr file.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino-manual)  
Buy the module: https://shillehtek.com/products/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino
