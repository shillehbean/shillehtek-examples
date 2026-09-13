// Two minimal Arduino sketches: one transmits a uint32 value over an NRF24L01+ using TMRh20's RF24 library, the other sends a 'hello' packet over LoRa using Sandeep Mistry's LoRa library.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-lora-vs-nrf24l01-radio-choice
// Parts used: https://shillehtek.com/products/nrf24l01-2-4ghz-wireless-transceiver-module-spi-for-arduino
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// NRF24L01+ with TMRh20 RF24 library
#include <RF24.h>
RF24 r(9, 10);
void setup() { r.begin(); r.openWritingPipe(0xF0F0F0F0E1LL); }
void loop() { uint32_t v=42; r.write(&v, sizeof(v)); delay(1000); }

// LoRa with Sandeep Mistry's LoRa library
#include <LoRa.h>
void setup() {
  LoRa.begin(433E6);   // or 868E6 / 915E6
}
void loop() {
  LoRa.beginPacket();
  LoRa.print("hello");
  LoRa.endPacket();
  delay(5000);
}
