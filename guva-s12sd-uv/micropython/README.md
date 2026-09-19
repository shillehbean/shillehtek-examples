# Micropython examples

- [`example_1.py`](./example_1.py) — Runs on an ESP32 with MicroPython: configures ADC on GPIO34 with 11dB attenuation, averages factory-calibrated microvolt readings (adc.read_uv()), converts to millivolts, estimates UV index as mV/100, and prints the result.
- [`example_2.py`](./example_2.py) — MicroPython example for the Raspberry Pi Pico: reads ADC0 (GP26) with read_u16(), averages samples, converts to millivolts using the Pico's 3.3V scale, estimates UV index as mV/100, and prints the readings.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/uv-sensor-guva-s12sd-arduino-esp32-manual)  
Buy the module: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
