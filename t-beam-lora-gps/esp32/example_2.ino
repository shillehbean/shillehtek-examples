// Initialize the SX1276 LoRa radio over SPI and transmit a simple beacon packet every 5 seconds at 915 MHz (antenna must be attached before powering the board).
//
// Buy this module: https://shillehtek.com/products/esp32-tbeam-lora-915mhz-neo6m-gps
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/esp32-tbeam-lora-915mhz-neo6m-gps-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// T-Beam (SX1276 revision) - send a LoRa packet every 5 seconds
// Library: "LoRa" by Sandeep Mistry. SX1262 boards: use RadioLib instead.
// ANTENNA MUST BE ATTACHED BEFORE POWERING THE BOARD.

#include <SPI.h>
#include <LoRa.h>

const long FREQ = 915E6;   // 915 MHz (US band)
int counter = 0;

void setup() {
  Serial.begin(115200);

  SPI.begin(5, 19, 27, 18);        // SCK, MISO, MOSI, NSS
  LoRa.setPins(18, 23, 26);        // NSS, RST, DIO0

  if (!LoRa.begin(FREQ)) {
    Serial.println("LoRa init failed - check antenna and revision");
    while (true) delay(1000);
  }
  Serial.println("LoRa ready");
}

void loop() {
  LoRa.beginPacket();
  LoRa.print("T-Beam beacon #");
  LoRa.print(counter++);
  LoRa.endPacket();

  Serial.println("Packet sent");
  delay(5000);
}
