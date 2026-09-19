# Micropython examples

- [`example_1.py`](./example_1.py) — Uses MicroPython on an ESP32 to read the KY-018 on GPIO34 via ADC, prints the 0–4095 raw value and a bright/dim/dark classification.
- [`example_2.py`](./example_2.py) — Uses MicroPython on a Raspberry Pi Pico to read the KY-018 on GP26 (ADC0), prints the 0–65535 raw reading and classifies ambient light as bright/dim/dark.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/photoresistor-light-sensor-ky-018-arduino-esp32-manual)  
Buy the module: https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
