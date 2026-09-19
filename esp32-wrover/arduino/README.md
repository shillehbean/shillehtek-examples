# Arduino examples

- [`example_1.ino`](./example_1.ino) — Prints ESP32 chip/flash/PSRAM info, allocates 1 MB in PSRAM to verify it's usable, and performs a WiFi network scan showing SSIDs and RSSI.
- [`example_2.ino`](./example_2.ino) — Connects the WROVER to WiFi, allocates a 2 MB PSRAM buffer, performs an HTTP GET to example.com, copies the response into PSRAM and prints the first line.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-wrover-4mb-psram-wifi-bluetooth-module-manual)  
Buy the module: https://shillehtek.com/products/esp32-wrover-4mb-psram-wifi-bluetooth-module
