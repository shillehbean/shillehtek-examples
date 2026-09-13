# Bash examples

- [`setup_meshtastic_env.sh`](./setup_meshtastic_env.sh) — Create and activate a Python virtual environment and install the Meshtastic CLI/package.
- [`configure_primary_node.sh`](./configure_primary_node.sh) — Open channel editing on a device and configure the primary channel name, a random pre-shared key, and the LoRa region, then commit the changes.
- [`show_primary_channel_url.sh`](./show_primary_channel_url.sh) — Query the device information and filter the output to show the Primary channel URL for sharing with other nodes.
- [`join_secondary_node.sh`](./join_secondary_node.sh) — Point a secondary node at the primary channel URL, set the LoRa region, and reboot the secondary node so it joins the network.
- [`reboot_primary_node.sh`](./reboot_primary_node.sh) — Reboot the primary device to apply settings or refresh its state.
- [`send_message_and_list_nodes.sh`](./send_message_and_list_nodes.sh) — Send a text message from the primary node and list known nodes on the network.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/esp32-sx1262-offline-mesh-messaging)  
Parts used: [CP2102 USB to TTL UART Serial Converter Module 6-Pin for Arduino, ESP32 & ESP8266](https://shillehtek.com/products/cp2102-usb-to-ttl-uart-serial-converter-module-6pin-for-arduino) · [FT232RL Mini USB to TTL Serial Converter 2-Pack 3.3V/5V for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-ft232rl-mini-usb-to-ttl-serial-converter-adapter-module-2pcs) · [ESP-WROOM-32 (ESP-32S) ESP32 Dev Board CP2102 USB-C Pre-Soldered](https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered)
