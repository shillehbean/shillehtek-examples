// Receives messages from a 433 MHz ASK receiver using the RadioHead RH_ASK driver on Arduino (RX on digital pin 11) and prints received text to the serial console.
//
// Buy this module: https://shillehtek.com/products/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// 433 MHz Receiver - Arduino
// Same library: RadioHead

#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver(2000, 11, 12);  // speed=2000bps, RX=D11, TX=D12(unused)

void setup() {
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("RH_ASK init failed");
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  if (driver.recv(buf, &buflen)) {
    buf[buflen] = 0;
    Serial.print("Got: ");
    Serial.println((char*)buf);
  }
}
