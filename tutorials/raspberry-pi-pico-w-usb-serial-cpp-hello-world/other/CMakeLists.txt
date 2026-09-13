# CMakeLists configuration for the Pico project: initialize the SDK, add the executable, enable USB stdio, link pico_stdlib, and create extra outputs (map/bin/hex/uf2).
#
# Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-usb-serial-cpp-hello-world
# Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# More examples: https://github.com/shillehbean/shillehtek-examples
#

cmake_minimum_required(VERSION 3.13)

# Include the Pico SDK initialization script
include($ENV{PICO_SDK_PATH}/pico_sdk_init.cmake)

project(my_project)

# Initialize the Pico SDK
pico_sdk_init()

# Add your executable and source files
add_executable(my_project
    main.cpp
)

# Enable USB stdio and disable UART stdio
pico_enable_stdio_usb(my_project 1)
pico_enable_stdio_uart(my_project 0)

# Link the Pico SDK to your project
target_link_libraries(my_project pico_stdlib)

# Create map/bin/hex/uf2 files
pico_add_extra_outputs(my_project)
