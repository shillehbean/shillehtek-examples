# Arduino Uno DHT11: PWM Fan Speed Control

This project builds an Arduino-based thermostat that reads temperature and humidity from a DHT11, displays live readings and the user setpoint on an I2C 16x2 LCD, and controls a DC fan with PWM. The code implements hysteresis to avoid rapid on/off chatter and ramps fan speed proportionally between the setpoint and a defined upper band.

**Read the full tutorial:** [Arduino Uno DHT11: PWM Fan Speed Control](https://shillehtek.com/blogs/news/arduino-uno-dht11-pwm-fan-controller)  
**Parts used:** [Arduino Uno R3 Super Starter Kit](https://shillehtek.com/products/arduino-uno-r3-starter-kit) · [DHT11 Temperature & Humidity Sensor](https://shillehtek.com/products/shillehtek-dht11-with-cables) · [LCD1602 16x2 Display](https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module) · [PCF8574 I2C Adapter](https://shillehtek.com/products/pcf8574-i2c-serial-interface-adapter-module-for-1602-2004-lcd) · [L298N Motor Driver](https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board) · [TB6612FNG](https://shillehtek.com/products/tb6612fng-dual-motor-driver-module-arduino-esp32) · [LM2596 Buck Converter](https://shillehtek.com/products/shillehtek-lm2596-dc-dc-adjustable-step-down-power-supply-module) · [830-Point Breadboard](https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers)

![Arduino Uno DHT11: PWM Fan Speed Control](https://cdn.shopify.com/s/files/1/0837/4340/8415/articles/blog-thumbnail-630435479839.png?v=1789300193)

## Examples in this folder

- [`arduino/`](./arduino/) — 1 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/arduino-uno-dht11-pwm-fan-controller](https://shillehtek.com/blogs/news/arduino-uno-dht11-pwm-fan-controller). Last verified: see commit history._
