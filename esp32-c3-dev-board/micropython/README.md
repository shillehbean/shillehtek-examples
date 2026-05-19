# Micropython examples

- [`example_1.py`](./example_1.py) — Uses MicroPython to scan the I2C bus on SDA=GPIO8 and SCL=GPIO9, printing any detected device addresses every two seconds.
- [`example_2.py`](./example_2.py) — Implements a minimal BLE peripheral in MicroPython that advertises as 'ESP32C3-Hello' and exposes a read-only Manufacturer Name characteristic returning 'ShillehTek'.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-c3-dev-board-4mb-wifi-presoldered-manual)  
Buy the module: https://shillehtek.com/products/esp32-c3-dev-board-4mb-wifi-presoldered
