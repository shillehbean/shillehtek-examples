# Blink the onboard LED using the Pico C SDK and the CYW43 driver (for pico2_w), toggling the LED via cyw43_arch_gpio_put.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2w-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

// Raspberry Pi Pico 2W - Pico SDK Blink Example
// On the Pico 2W, the onboard LED is driven through the CYW43 driver.
// Build with pico-sdk >= 2.0.0 and PICO_BOARD=pico2_w.

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int main() {
    if (cyw43_arch_init()) {
        return -1;
    }
    while (true) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
        sleep_ms(500);
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
        sleep_ms(500);
    }
}
