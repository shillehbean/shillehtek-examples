// Receives LoRa packets with the Arduino 'LoRa' library and prints the message, RSSI, and SNR to Serial.
//
// Buy this module: https://shillehtek.com/products/sx1278-lora-433mhz-transceiver-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/sx1278-lora-433mhz-transceiver-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Ra-02 SX1278 - LoRa Receiver (Arduino IDE)
// Same library and settings as the sender.

#include <SPI.h>
#include <LoRa.h>

void setup() {
  Serial.begin(115200);
  LoRa.setPins(5, 14, 26);

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(9);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setSyncWord(0x12);
  Serial.println("LoRa receiver ready");
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String msg = "";
    while (LoRa.available()) {
      msg += (char)LoRa.read();
    }
    Serial.print("Received: '");
    Serial.print(msg);
    Serial.print("'  RSSI: ");
    Serial.print(LoRa.packetRssi());
    Serial.print(" dBm  SNR: ");
    Serial.println(LoRa.packetSnr());
  }
}
