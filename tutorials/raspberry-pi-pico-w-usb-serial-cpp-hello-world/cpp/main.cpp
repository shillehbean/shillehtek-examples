// Main C++ program that initializes stdio and prints "Hello, World!" over USB serial once per second.
//
// Full tutorial: https://shillehtek.com/blogs/news/raspberry-pi-pico-w-usb-serial-cpp-hello-world
// Parts used: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "pico/stdlib.h"
#include <cstdio> // Include the C standard IO functions

int main() {
    stdio_init_all(); // Initialize standard IO

    while (true) {
        printf("Hello, World!\n");
        sleep_ms(1000);
    }
}
