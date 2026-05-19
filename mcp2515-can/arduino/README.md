# Arduino examples

- [`example_1.ino`](./example_1.ino) — Initializes the MCP2515 at 500 kbps over SPI and transmits an 8-byte CAN frame (ID 0x100) once per second, reporting success to Serial.
- [`example_2.ino`](./example_2.ino) — Initializes the MCP2515 and polls for incoming CAN frames, printing the received message ID and payload bytes to Serial when a frame arrives.

Full wiring + setup notes: [manual](https://shillehtek.com/blogs/shillehtek-product-manuals/mcp2515-can-bus-module-tja1050-receiver-spi-manual)  
Buy the module: https://shillehtek.com/products/mcp2515-can-bus-module-tja1050-receiver-spi
