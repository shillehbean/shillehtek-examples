# Esp32 examples

- [`soil_moisture_serial.ino`](./soil_moisture_serial.ino) — Reads the analog moisture sensor on ADC pin 34, converts the 12-bit ADC value to a percentage, and prints the moisture percent to Serial every second.
- [`wifi_credentials.ino`](./wifi_credentials.ino) — Placeholder constants for the Wi‑Fi SSID and password to be used by the ESP32 web server sketch.
- [`soil_moisture_server.ino`](./soil_moisture_server.ino) — ESP32 web server sketch that hosts a simple HTML dashboard and an endpoint (/readMoisture) to return the current moisture percentage to the page's JavaScript.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/esp32-soil-moisture-sensor-wifi-dashboard-readout)  
Parts used: [ESP-WROOM-32 (ESP-32S) ESP32 Dev Board CP2102 USB-C Pre-Soldered](https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered)
