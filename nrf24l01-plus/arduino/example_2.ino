// A basic receiver sketch that initializes the nRF24L01+, opens a reading pipe, listens for incoming packets, and prints received text to Serial when available.
//
// Buy this module: https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

#include <SPI.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
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
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.print("RX: ");
    Serial.println(text);
  }
}
