# Raspberry Pi Pico W MPU6050: Send data to DynamoDB

This tutorial shows how to read accelerometer/gyroscope data from an MPU6050 on a Raspberry Pi Pico W and send it securely to AWS DynamoDB via AWS IoT Core and MQTT. The folder contains the MicroPython client that runs on the Pico W (I2C + MQTT + certificate handling) and an example AWS Lambda function that writes incoming events to a DynamoDB table.

**Read the full tutorial:** [Raspberry Pi Pico W MPU6050: Send data to DynamoDB](https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mpu6050-send-data-dynamodb)  
**Parts used:** [MPU6050 Pre-Soldered IMU Accelerometer Sensor 2-Pack for Arduino](https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer) · [MPU6050 GY-521 V2 Unsoldered IMU Accelerometer & Gyroscope Sensor for Arduino](https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version) · [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)

![Raspberry Pi Pico W MPU6050: Send data to DynamoDB](https://shillehtek.com/cdn/shop/articles/blog-thumbnail-606749393183.png?v=1782433847)

## Examples in this folder

- [`micropython/`](./micropython/) — 1 sample(s)
- [`python/`](./python/) — 1 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mpu6050-send-data-dynamodb](https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mpu6050-send-data-dynamodb). Last verified: see commit history._
