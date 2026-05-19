// Reads an RFID tag UID via SPI and prints the UID bytes to the Arduino Serial monitor when a card or fob is tapped.
//
// Buy this module: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-spi-kit-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/rc522-rfid-reader-writer-module-13-56mhz-spi-kit-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// RC522 RFID - Arduino Example
// Library: MFRC522 by GithubCommunity

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
  Serial.println("Tap an RFID card or fob...");
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}
