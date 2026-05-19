// Sends a repeating "Hello, world!" message over a 433 MHz ASK transmitter using the RadioHead RH_ASK driver on Arduino (TX on digital pin 12).
//
// Buy this module: https://shillehtek.com/products/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// 433 MHz Transmitter - Arduino
// Library: RadioHead by airspayce.com (Arduino Library Manager)

#include <RH_ASK.h>
#include <SPI.h>  // RadioHead requires SPI.h even when not using SPI

RH_ASK driver(2000, 11, 12);  // speed=2000bps, RX=D11(unused), TX=D12

void setup() {
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("RH_ASK init failed");
}

void loop() {
  const char *msg = "Hello, world!";
  driver.send((uint8_t*)msg, strlen(msg));
  driver.waitPacketSent();
  Serial.println("Sent");
  delay(1000);
}
