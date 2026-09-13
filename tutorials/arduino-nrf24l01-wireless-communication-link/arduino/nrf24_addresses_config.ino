// Snippet showing how to define two pipe addresses and configure each node to use one address for writing and the other for reading (swap for the second node).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nrf24l01-wireless-communication-link
// Parts used: https://shillehtek.com/products/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range
//             https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const byte addresses[][10] = {"ADDRESS01", "ADDRESS02"};

// Node 1 setup:
radio.openWritingPipe(addresses[0]);
radio.openReadingPipe(1, addresses[1]);

// Node 2 setup (swapped):
radio.openWritingPipe(addresses[1]);
radio.openReadingPipe(1, addresses[0]);
