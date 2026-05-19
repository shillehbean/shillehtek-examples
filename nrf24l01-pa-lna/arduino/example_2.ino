// Listens for incoming nRF24L01 packets on the specified pipe and prints received messages to Serial, configured for PA/LNA use and 250kbps data rate.
//
// Buy this module: https://shillehtek.com/products/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range-manual
// More examples: https://github.com/shillehtek/examples
//

// NRF24L01+ PA LNA - Arduino RX
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "NODE1";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);
  radio.setDataRate(RF24_250KBPS);
  radio.openReadingPipe(0, address);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    Serial.print("Got: "); Serial.println(text);
  }
}
