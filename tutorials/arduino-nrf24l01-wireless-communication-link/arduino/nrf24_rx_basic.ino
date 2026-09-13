// A minimal NRF24L01 receiver that listens for incoming messages and prints received text to the serial console.
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
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.println(text);
  }
}
