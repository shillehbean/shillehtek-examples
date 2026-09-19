# Esp32 examples

- [`example_1.ino`](./example_1.ino) — Power the NEO-6M via the AXP PMU, read NMEA sentences from the GPS over Serial1, parse them with TinyGPSPlus, and print latitude, longitude, and satellite count to the USB serial console.
- [`example_2.ino`](./example_2.ino) — Initialize the SX1276 LoRa radio over SPI and transmit a simple beacon packet every 5 seconds at 915 MHz (antenna must be attached before powering the board).

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-tbeam-lora-915mhz-neo6m-gps-manual)  
Buy the module: https://shillehtek.com/products/esp32-tbeam-lora-915mhz-neo6m-gps
