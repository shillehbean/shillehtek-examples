// Initializes the RC522 via SPI, detects MIFARE cards/key fobs, and prints their UID in hexadecimal to the Serial Monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-rc522-read-uid
// Parts used: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-spi-kit-for-arduino
//             https://shillehtek.com/products/13-56mhz-rfid-smart-card-s50-1k-chip-iso14443a-access-control
//             https://shillehtek.com/products/13-56mhz-rfid-key-fob-tag-ic-s50-token-iso14443a-access-control
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <MFRC522.h>

const int RST_PIN = 9;
const int SS_PIN  = 10;
MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Tap a card...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print('0');
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) Serial.print(':');
  }
  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
