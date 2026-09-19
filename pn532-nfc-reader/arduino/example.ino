// Reads a passive ISO14443A NFC tag over I2C with the Adafruit PN532 Arduino library and prints the tag UID to Serial.
//
// Buy this module: https://shillehtek.com/products/pn532-nfc-rfid-reader-writer-module-v3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pn532-nfc-rfid-reader-writer-module-v3-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PN532 NFC Module V3 - Arduino Example (I2C mode)
// SDA->A4, SCL->A5, VCC->5V | S1=ON, S2=OFF
// Library: "Adafruit PN532" (Library Manager)

#include <Wire.h>
#include <Adafruit_PN532.h>

Adafruit_PN532 nfc(-1, -1, &Wire);   // I2C, no IRQ/RSTO pins needed

void setup() {
  Serial.begin(115200);
  nfc.begin();

  uint32_t version = nfc.getFirmwareVersion();
  if (!version) {
    Serial.println("Didn't find PN53x board - check S1/S2 and wiring");
    while (1);
  }
  Serial.print("Found PN5");
  Serial.println((version >> 24) & 0xFF, HEX);

  nfc.SAMConfig();                   // enable reader mode
  Serial.println("Tap a card or tag...");
}

void loop() {
  uint8_t uid[7];
  uint8_t uidLength;

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 500)) {
    Serial.print("Card UID: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      if (uid[i] < 0x10) Serial.print("0");
      Serial.print(uid[i], HEX);
      if (i < uidLength - 1) Serial.print(":");
    }
    Serial.println();
    delay(1000);                     // debounce same-card reads
  }
}
