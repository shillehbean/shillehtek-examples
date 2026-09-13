// Reads RFID card UIDs with an MFRC522 connected over SPI, prints the UID to Serial, and grants or denies access by comparing the UID to a hard-coded authorized value.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-mfrc522-rfid-access-control
// Parts used: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-spi-kit-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.println("Approximate your card to the reader...");
  Serial.println();
}

void loop()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("UID tag :");
  String content = "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();

  if (content.substring(1) == "BD 31 15 2B")  // Replace with YOUR tag UID
  {
    Serial.println("Authorized access");
    Serial.println();
    delay(3000);
  }
  else
  {
    Serial.println("Access denied");
    delay(3000);
  }
}
