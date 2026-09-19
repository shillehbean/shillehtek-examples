# Micropython examples

- [`example_1.py`](./example_1.py) — Shows esptool commands to flash a MicroPython SPIRAM build, then in the REPL prints CPU/flash info, reports free RAM and allocates a 2 MB bytearray in PSRAM to verify availability.
- [`example_2.py`](./example_2.py) — Performs a WiFi scan under MicroPython (printing SSID, channel and RSSI) and provides a small connect(ssid, password) helper that waits for association.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-wrover-4mb-psram-wifi-bluetooth-module-manual)  
Buy the module: https://shillehtek.com/products/esp32-wrover-4mb-psram-wifi-bluetooth-module
