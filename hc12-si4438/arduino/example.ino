// Simple Arduino transparent serial bridge that relays data between the PC Serial Monitor and an HC-12 using SoftwareSerial on D10 (RX) / D11 (TX).
//
// Buy this module: https://shillehtek.com/products/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-12-433mhz-serial-transceiver-si4438-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HC-12 - Arduino transparent link (chat bridge)
// TXD->D10, RXD->D11, VCC->5V | flash the same sketch on both boards

#include <SoftwareSerial.h>

SoftwareSerial hc12(10, 11);   // RX, TX

void setup() {
  Serial.begin(9600);
  hc12.begin(9600);            // HC-12 default baud
  Serial.println("HC-12 chat ready - type and press enter");
}

void loop() {
  // radio -> serial monitor
  while (hc12.available()) {
    Serial.write(hc12.read());
  }
  // serial monitor -> radio
  while (Serial.available()) {
    hc12.write(Serial.read());
  }
}
