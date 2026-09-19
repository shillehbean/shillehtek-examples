# Esp32 examples

- [`zigbee_light_node.ino`](./zigbee_light_node.ino) — ESP32-C6 Zigbee end-device sketch that implements a light endpoint which controls a local LED via received Zigbee commands and uses a button for factory reset.
- [`zigbee_coordinator_switch.ino`](./zigbee_coordinator_switch.ino) — ESP32-C6 Zigbee coordinator sketch that forms a Zigbee network and exposes a switch endpoint which can send on/off commands to paired light endpoints when the button is used.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/esp32-c6-zigbee-light-switch-network)  
Parts used: [ESP32-C6-N4 Pre-Soldered Development Board](https://shillehtek.com/products/esp32-c6-n4-dev-board-presoldered) · [Seeed XIAO ESP32-C6](https://shillehtek.com/products/xiao-seeed-esp32c6-pre-soldered-with-usb-c-cable) · [Resistor Kit](https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box) · [400-Point Breadboard](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Dupont Jumper Wires](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire) · [Tactile Button Kit](https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm)
