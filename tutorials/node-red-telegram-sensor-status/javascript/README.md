# Javascript examples

- [`telegram_status_function.js`](./telegram_status_function.js) — Node-RED function node that responds to a Telegram "status" command by reading latest temperature and pressure from flow context and sending a formatted message back to the chat.
- [`store_sensor_readings.js`](./store_sensor_readings.js) — Node-RED function node that stores incoming sensor payload values (temp and pressure) into flow context for later retrieval.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/node-red-telegram-sensor-status)  
Parts used: [BMP180 Pre-Soldered Pressure & Temperature Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-bmp180-pre-soldered)
