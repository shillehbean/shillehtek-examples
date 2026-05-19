// A simple transmitter sketch that initializes the nRF24L01+, opens a writing pipe, and sends a "Hello World" packet once per second while printing transmission status to Serial.
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
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello World";
  bool ok = radio.write(&text, sizeof(text));
  Serial.println(ok ? "TX ok" : "TX fail");
  delay(1000);
}
