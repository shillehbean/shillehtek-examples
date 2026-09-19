# Arduino Uno + Nano I2C: Send DHT11 Data to OLED

This tutorial shows how to link an Arduino Nano (peripheral) and an Arduino Uno (controller) over I2C so the Nano reads a DHT11 sensor and the Uno displays the temperature and humidity on an SSD1306 OLED. The code in this folder contains the Nano peripheral sketch that reads the DHT11 and responds to I2C requests, and the Uno master sketch that requests the sensor data, displays it on the OLED, and sends a simple LED control command back to the Nano.

**Read the full tutorial:** [Arduino Uno + Nano I2C: Send DHT11 Data to OLED](https://shillehtek.com/blogs/news/arduino-uno-nano-i2c-dht11-oled-display)  
**Parts used:** [Arduino Nano V3.0 Pre-Soldered](https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p) · [Arduino Uno R3 Super Starter Kit](https://shillehtek.com/products/arduino-uno-r3-starter-kit) · [DHT11 Temperature & Humidity Sensor](https://shillehtek.com/products/shillehtek-dht11-with-cables) · [0.96" I2C OLED (SSD1306)](https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306) · [Resistor Kit](https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box) · [830-Point Breadboard](https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)

![Arduino Uno + Nano I2C: Send DHT11 Data to OLED](https://cdn.shopify.com/s/files/1/0837/4340/8415/articles/blog-thumbnail-630435447071.png?v=1789300159)

## Examples in this folder

- [`arduino/`](./arduino/) — 2 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/arduino-uno-nano-i2c-dht11-oled-display](https://shillehtek.com/blogs/news/arduino-uno-nano-i2c-dht11-oled-display). Last verified: see commit history._
