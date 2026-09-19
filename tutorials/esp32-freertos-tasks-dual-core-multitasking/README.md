# ESP32 FreeRTOS Tasks: Dual-core multitasking guide

This tutorial demonstrates using FreeRTOS on an ESP32 to run dual-core tasks: a minimal blink example and a producer/consumer example that reads a DHT11 and updates an SSD1306 OLED. The code shows how to pin tasks to cores, create a queue for sensor readings, and keep the display responsive while sampling the sensor periodically.

**Read the full tutorial:** [ESP32 FreeRTOS Tasks: Dual-core multitasking guide](https://shillehtek.com/blogs/news/esp32-freertos-tasks-dual-core-multitasking)  
**Parts used:** [ESP32 38-Pin Dev Board (CP2102, USB-C)](https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb) · [DHT11 Temperature & Humidity Sensor](https://shillehtek.com/products/shillehtek-dht11-with-cables) · [SSD1306 0.96" I2C OLED](https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306) · [XIAO ESP32-C6](https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable) · [400-Point Breadboard](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)

![ESP32 FreeRTOS Tasks: Dual-core multitasking guide](https://cdn.shopify.com/s/files/1/0837/4340/8415/articles/blog-thumbnail-630434857247.png?v=1789290407)

## Examples in this folder

- [`esp32/`](./esp32/) — 2 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/esp32-freertos-tasks-dual-core-multitasking](https://shillehtek.com/blogs/news/esp32-freertos-tasks-dual-core-multitasking). Last verified: see commit history._
