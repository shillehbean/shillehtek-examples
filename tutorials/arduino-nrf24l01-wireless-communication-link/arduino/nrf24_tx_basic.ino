// A minimal NRF24L01 transmitter that sends a fixed text string once per second over SPI using the RF24 library.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nrf24l01-wireless-communication-link
// Parts used: https://shillehtek.com/products/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range
//             https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello from TX";
  radio.write(&text, sizeof(text));
  delay(1000);
}
