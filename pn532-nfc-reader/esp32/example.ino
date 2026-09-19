// Uses ESP32 I2C to read a card UID with the Adafruit PN532 library, compares it to a whitelist UID, and prints an access-granted or unknown message.
//
// Buy this module: https://shillehtek.com/products/pn532-nfc-rfid-reader-writer-module-v3
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pn532-nfc-rfid-reader-writer-module-v3-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PN532 NFC Module V3 - ESP32 Example (I2C mode)
// SDA->GPIO 21, SCL->GPIO 22, VCC->3V3 | S1=ON, S2=OFF
// Library: "Adafruit PN532"

#include <Wire.h>
#include <Adafruit_PN532.h>

Adafruit_PN532 nfc(-1, -1, &Wire);

// Example whitelist: replace with your own card UID
const uint8_t DOOR_CARD[4] = {0xDE, 0xAD, 0xBE, 0xEF};

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  nfc.begin();

  if (!nfc.getFirmwareVersion()) {
    Serial.println("PN532 not found - check S1/S2 switches");
    while (1) delay(10);
  }
  nfc.SAMConfig();
  Serial.println("Tap a card or tag...");
}

void loop() {
  uint8_t uid[7];
  uint8_t len;

  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &len, 500)) {
    Serial.print("UID: ");
    for (uint8_t i = 0; i < len; i++) {
      Serial.printf("%02X", uid[i]);
      if (i < len - 1) Serial.print(":");
    }

    bool match = (len == 4) && !memcmp(uid, DOOR_CARD, 4);
    Serial.println(match ? "  -> ACCESS GRANTED" : "  -> unknown card");
    delay(1000);
  }
}
