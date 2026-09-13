# Python examples

- [`lambda_write_dynamodb.py`](./lambda_write_dynamodb.py) — AWS Lambda function that receives an event containing MPU6050 data and writes the point_number, ax value (as a Decimal) and topic into the DynamoDB table named 'MPU6050'.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/raspberry-pi-pico-w-mpu6050-send-data-dynamodb)  
Parts used: [MPU6050 Pre-Soldered IMU Accelerometer Sensor 2-Pack for Arduino](https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer) · [MPU6050 GY-521 V2 Unsoldered IMU Accelerometer & Gyroscope Sensor for Arduino](https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version) · [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
