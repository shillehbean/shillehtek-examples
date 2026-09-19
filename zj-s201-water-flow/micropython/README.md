# Micropython examples

- [`example_1.py`](./example_1.py) — ESP32 MicroPython script that attaches a falling-edge IRQ on GPIO27 to count pulses, calculating and printing flow rate (L/min) and total volume each second.
- [`example_2.py`](./example_2.py) — Raspberry Pi Pico MicroPython example that counts pulses on GP15 to compute flow and total volume and uses the onboard LED as a simple leak alarm when flow exceeds a small threshold.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/water-flow-sensor-g1-2-1-30l-min-manual)  
Buy the module: https://shillehtek.com/products/water-flow-sensor-g1-2-1-30l-min
