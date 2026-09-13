# CMake build script that configures and links a Raspberry Pi Pico C++ project for reading the MPU6050 over I2C.
#
# Full tutorial: https://shillehtek.com/blogs/news/pico-w-mpu6050-read-imu-data-cpp
# Parts used: https://shillehtek.com/products/mpu-6050-pre-soldered-6-dof-accelerometer
#             https://shillehtek.com/products/shillehtek-mpu-6050-module-gy-521-module-unsoldered-version
#             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
# More examples: https://github.com/shillehbean/shillehtek-examples
#

cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK using the environment variable
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(mpu6050_i2c_example)

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Create an executable for the project
add_executable(mpu6050_i2c_example
    main.cpp
)

# Link the necessary libraries
target_link_libraries(mpu6050_i2c_example pico_stdlib hardware_i2c)

# Enable USB output
pico_enable_stdio_usb(mpu6050_i2c_example 1)
# Disable UART output
pico_enable_stdio_uart(mpu6050_i2c_example 0)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(mpu6050_i2c_example)
