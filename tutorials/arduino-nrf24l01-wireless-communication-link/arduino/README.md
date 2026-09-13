# Arduino examples

- [`nrf24_tx_basic.ino`](./nrf24_tx_basic.ino) — A minimal NRF24L01 transmitter that sends a fixed text string once per second over SPI using the RF24 library.
- [`nrf24_rx_basic.ino`](./nrf24_rx_basic.ino) — A minimal NRF24L01 receiver that listens for incoming messages and prints received text to the serial console.
- [`nrf24_addresses_config.ino`](./nrf24_addresses_config.ino) — Snippet showing how to define two pipe addresses and configure each node to use one address for writing and the other for reading (swap for the second node).

Full walkthrough: [tutorial](https://shillehtek.com/blogs/news/arduino-nrf24l01-wireless-communication-link)  
Parts used: [NRF24L01+ PA LNA Wireless Transceiver Module with Antenna, 1100m Range](https://shillehtek.com/products/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range) · [NRF24L01+ 2.4GHz Wireless Transceiver Module SPI for Arduino & Raspberry Pi](https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino)
