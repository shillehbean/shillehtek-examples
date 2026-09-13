# Other examples

- [`create_iotdata_table.kql`](./create_iotdata_table.kql) — Kusto (ADX) command to create an 'iotdata' table schema for device telemetry.
- [`create_ingestion_mapping.kql`](./create_ingestion_mapping.kql) — Kusto (ADX) command to create a JSON ingestion mapping named 'iotmap' for the iotdata table.
- [`query_recent_iotdata.kql`](./query_recent_iotdata.kql) — Kusto (ADX) query to return iotdata records from the last 10 minutes ordered by timestamp descending.
- [`query_avg_temperature_timechart.kql`](./query_avg_temperature_timechart.kql) — Kusto (ADX) query to compute and render a 1‑minute binned timechart of average temperature from iotdata.

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/raspberry-pi-pico-w-bme280-azure-iot-pipeline)  
Parts used: [BME280 Pre-Soldered Temperature, Pressure & Humidity Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor) · [120pcs 20cm Dupont Jumper Wires for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire) · [120pcs 10cm Jumper Wire Set M-F, M-M, F-F for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire) · [830 Point Solderless Breadboard for Arduino, Raspberry Pi & ESP32](https://shillehtek.com/products/shillehtek-830-point-breadboard-for-arduino-raspberry-pi-esp32-and-other-microcontrollers) · [400-Point Small Solderless Breadboard for Arduino, Raspberry Pi & ESP32](https://shillehtek.com/products/shillehtek-400-point-breadboard) · [Raspberry Pi Pico 2W with Pre-Soldered Headers](https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers)
