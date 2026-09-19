# Micropython examples

- [`example_1.py`](./example_1.py) — Performs raw I2C reads from the MPU6050 on a Raspberry Pi Pico running MicroPython, unpacks the sensor registers, scales accel/gyro/temperature to physical units, and prints them repeatedly.
- [`example_2.py`](./example_2.py) — On an ESP32 running MicroPython, scans I2C, wakes the MPU6050, reads raw sensor registers, scales accelerometer and gyroscope values to physical units, and prints the results continuously.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/mpu6050-accelerometer-6dof-raspberry-pi-arduino-esp32-i2c-accelerometer)  
Buy the module: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
