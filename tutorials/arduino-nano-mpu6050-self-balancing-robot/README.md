# Arduino Nano MPU6050: Build a Self-Balancing Robot

This project builds a two-wheeled self-balancing robot using an Arduino Nano, an MPU-6050 accelerometer/gyroscope, and an L298N motor driver. The code reads the MPU-6050 over I2C, fuses accelerometer and gyro data into an angle estimate, and runs a PID loop to drive the motors to keep the robot balanced. The provided file contains pin mappings, PID/complementary-filter tuning, and helper functions for MPU-6050 I2C read/write.

**Read the full tutorial:** [Arduino Nano MPU6050: Build a Self-Balancing Robot](https://shillehtek.com/blogs/news/arduino-nano-mpu6050-self-balancing-robot)  
**Parts used:** [Arduino Nano V3.0 Pre-Soldered](https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p) · [MPU-6050 Accelerometer/Gyro (pre-soldered)](https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer) · [L298N Motor Driver](https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board) · [TT Gear Motor 1:48](https://shillehtek.com/products/tt-gear-motor-3-6v-1-48-125rpm) · [Electrolytic Capacitor Kit](https://shillehtek.com/products/200pcs-electrolytic-capacitors-0-1uf-50v-220uf-10v-kit-plastic-box) · [400-Point Breadboard](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)

![Arduino Nano MPU6050: Build a Self-Balancing Robot](https://cdn.shopify.com/s/files/1/0837/4340/8415/articles/blog-thumbnail-630436102431.png?v=1789309294)

## Examples in this folder

- [`arduino/`](./arduino/) — 1 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/arduino-nano-mpu6050-self-balancing-robot](https://shillehtek.com/blogs/news/arduino-nano-mpu6050-self-balancing-robot). Last verified: see commit history._
