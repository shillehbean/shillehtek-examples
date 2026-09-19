# Esp32 examples

- [`dual_core_blink.ino`](./dual_core_blink.ino) — Creates two FreeRTOS tasks pinned to separate cores that blink two GPIO pins at different rates.
- [`dht_oled_freertos.ino`](./dht_oled_freertos.ino) — Implements a FreeRTOS producer/consumer pattern where a sensor task reads DHT11 values and sends them over a queue to a display task that updates an SSD1306 OLED.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/esp32-freertos-tasks-dual-core-multitasking)  
Parts used: [ESP32 38-Pin Dev Board (CP2102, USB-C)](https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb) · [DHT11 Temperature & Humidity Sensor](https://shillehtek.com/products/shillehtek-dht11-with-cables) · [SSD1306 0.96" I2C OLED](https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306) · [XIAO ESP32-C6](https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable) · [400-Point Breadboard](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)
