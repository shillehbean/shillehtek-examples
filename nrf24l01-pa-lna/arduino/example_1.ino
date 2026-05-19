// Transmits a periodic "Hello from PA LNA!" packet from an Arduino using the RF24 library with PA/LNA enabled and 250kbps data rate.
//
// Buy this module: https://shillehtek.com/products/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range-manual
// More examples: https://github.com/shillehtek/examples
//

// NRF24L01+ PA LNA - Arduino TX
// Library: RF24 by TMRh20 (Arduino Library Manager)

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10);  // CE, CSN
const byte address[6] = "NODE1";

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_HIGH);  // for PA LNA, RF24_PA_HIGH is sweet spot
  radio.setDataRate(RF24_250KBPS);  // longest range
  radio.openWritingPipe(address);
  radio.stopListening();
}

void loop() {
  const char text[] = "Hello from PA LNA!";
  bool ok = radio.write(&text, sizeof(text));
  Serial.println(ok ? "Sent OK" : "Send failed");
  delay(1000);
}
