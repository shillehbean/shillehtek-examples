# Micropython examples

- [`example_1.py`](./example_1.py) — Runs on an ESP32 with MicroPython: reads the divided analog signal on GPIO34 using ADC read_uv(), compensates for a 10k/20k voltage divider, converts voltage to wind speed, and prints values.
- [`example_2.py`](./example_2.py) — Runs on a Raspberry Pi Pico with MicroPython to read GP26 (ADC0), average ADC readings, undo the voltage divider, compute wind speed in m/s and mph, and print the values.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/anemometer-wind-speed-0-5v-analog-output-manual)  
Buy the module: https://shillehtek.com/products/anemometer-wind-speed-0-5v-analog-output
