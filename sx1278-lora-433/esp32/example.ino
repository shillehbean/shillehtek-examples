// Sends periodic LoRa packets from an ESP32 using the Arduino 'LoRa' library (SX1278 at 433 MHz).
//
// Buy this module: https://shillehtek.com/products/sx1278-lora-433mhz-transceiver-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1278-lora-433mhz-transceiver-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Ra-02 SX1278 - LoRa Sender (Arduino IDE)
// Library: "LoRa" by Sandeep Mistry (Library Manager)
// ESP32 pins: NSS=5, RESET=14, DIO0=26 (change for your wiring)

#include <SPI.h>
#include <LoRa.h>

const long FREQ = 433E6;
int counter = 0;

void setup() {
  Serial.begin(115200);
  LoRa.setPins(5, 14, 26);          // NSS, RESET, DIO0

  if (!LoRa.begin(FREQ)) {
    Serial.println("LoRa init failed - check wiring/antenna!");
    while (1);
  }
  LoRa.setSpreadingFactor(9);       // 7 = fast, 12 = max range
  LoRa.setSignalBandwidth(125E3);
  LoRa.setTxPower(17);              // dBm (max 20)
  LoRa.setSyncWord(0x12);           // private-network marker
  Serial.println("LoRa sender ready");
}

void loop() {
  Serial.print("Sending packet ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("Hello #");
  LoRa.print(counter++);
  LoRa.endPacket();

  delay(2000);
}
