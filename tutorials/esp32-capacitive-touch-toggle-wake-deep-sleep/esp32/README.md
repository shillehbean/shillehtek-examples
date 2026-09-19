# Esp32 examples

- [`touch_toggle.ino`](./touch_toggle.ino) — Read an ESP32 capacitive touch pad, debounce touches, toggle an LED (or relay input) and print ON/OFF to Serial.
- [`touch_wake_deepsleep.ino`](./touch_wake_deepsleep.ino) — Configure a touch pad interrupt and enable touchpad wake from deep sleep; blink the output on boot then enter deep sleep to wait for a touch to wake the ESP32.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/esp32-capacitive-touch-toggle-wake-deep-sleep)  
Parts used: [ESP32 38-Pin Dev Board (CP2102, USB-C)](https://shillehtek.com/products/esp32-dev-board-cp2102-type-c-4mb) · [1-Channel 5V Relay Module](https://shillehtek.com/products/1-channel-5v-relay-module) · [Resistor Kit](https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box) · [400-Point Breadboard](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire)
