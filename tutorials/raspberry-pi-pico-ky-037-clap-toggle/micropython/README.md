# Micropython examples

- [`clap_toggle_relay.py`](./clap_toggle_relay.py) — MicroPython script for Raspberry Pi Pico that reads the KY-037 digital output and toggles a relay and the onboard LED when a clap/sound pulse is detected, using a cooldown debounce and an 'armed' re-arm on silence.
- [`sound_sensor_monitor.py`](./sound_sensor_monitor.py) — Simple MicroPython test script that continuously reads the KY-037 digital output, prints the value, and mirrors it to the onboard LED so you can verify sensor behavior.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/raspberry-pi-pico-ky-037-clap-toggle)  
Parts used: [KY-037 Sound Sensor Module for Arduino & ESP32](https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module) · [400-Point Small Solderless Breadboard for Arduino, Raspberry Pi & ESP32](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
