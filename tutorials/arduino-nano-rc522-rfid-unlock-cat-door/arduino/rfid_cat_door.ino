// Reads RFID tags with an RC522 module and actuates a servo to unlock the cat door for UIDs listed as allowed.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-rc522-rfid-unlock-cat-door
// Parts used: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-spi-kit-for-arduino
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
//             https://shillehtek.com/products/13-56mhz-rfid-key-fob-tag-ic-s50-token-iso14443a-access-control
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>
const int RST_PIN = 9, SS_PIN = 10;
MFRC522 rfid(SS_PIN, RST_PIN);
Servo lock;
const byte ALLOWED[][4] = {
  {0x12, 0x34, 0x56, 0x78}    // replace with your cat's UID
};
void setup() {
  SPI.begin(); rfid.PCD_Init();
  lock.attach(6); lock.write(0);   // locked
}
bool isAllowed(byte* uid) {
  for (auto& tag : ALLOWED) {
    if (memcmp(uid, tag, 4) == 0) return true;
  }
  return false;
}
void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;
  if (isAllowed(rfid.uid.uidByte)) {
    lock.write(90); delay(8000); lock.write(0);   // 8 seconds to slip through
  }
  rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();
}
