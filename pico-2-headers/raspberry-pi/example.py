# Blink the onboard LED using the Raspberry Pi Pico C SDK (pico-sdk) by initializing GPIO 25 and toggling it with 500 ms delays.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2-usb-c-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2-usb-c-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

// Raspberry Pi Pico 2 - Pico SDK Blink Example
// Build with the official pico-sdk (>= 2.0.0 for RP2350 support)

#include "pico/stdlib.h"

int main() {
    const uint LED_PIN = 25;
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true) {
        gpio_put(LED_PIN, 1);
        sleep_ms(500);
        gpio_put(LED_PIN, 0);
        sleep_ms(500);
    }
}
