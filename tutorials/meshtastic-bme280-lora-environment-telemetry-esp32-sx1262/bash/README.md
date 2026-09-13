# Bash examples

- [`setup-meshtastic-env.sh`](./setup-meshtastic-env.sh) — Create a Python virtual environment and install the Meshtastic CLI package.
- [`meshtastic_config_channel.sh`](./meshtastic_config_channel.sh) — Begin editing the device config, set the primary channel name and PSK, set the LoRa region, and commit the changes.
- [`meshtastic_show_channel_url.sh`](./meshtastic_show_channel_url.sh) — Query the device for its info and extract the primary channel URL.
- [`meshtastic_apply_channel_url.sh`](./meshtastic_apply_channel_url.sh) — Apply a channel URL to a device, set the LoRa region, and reboot the node.
- [`meshtastic_reboot.sh`](./meshtastic_reboot.sh) — Reboot the Meshtastic device attached at the given serial port.
- [`meshtastic_enable_telemetry_env.sh`](./meshtastic_enable_telemetry_env.sh) — Enable environment telemetry, set the environment telemetry update interval, and enable the environment telemetry screen on the device.
- [`meshtastic_enable_telemetry_screen.sh`](./meshtastic_enable_telemetry_screen.sh) — Enable the environment telemetry screen on a device connected to a specific serial port.
- [`meshtastic_request_env_telemetry.sh`](./meshtastic_request_env_telemetry.sh) — Request environment telemetry from a remote node by destination ID and wait up to a timeout.
- [`meshtastic_list_nodes.sh`](./meshtastic_list_nodes.sh) — List known nodes visible to the local Meshtastic device.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/meshtastic-bme280-lora-environment-telemetry-esp32-sx1262)  
Parts used: [BME280 Pre-Soldered Temperature, Pressure & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [400-Point Small Solderless Breadboard for Arduino, Raspberry Pi & ESP32](https://shillehtek.com/products/shillehtek-400-point-breadboard)
