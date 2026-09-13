// Arduino sketch that reads RC522 RFID tags, shows status on an SSD1306 OLED, and actuates a servo to lock/unlock based on authorized UIDs.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-rc522-rfid-smart-door-lock-oled
// Parts used: https://shillehtek.com/products/rc522-rfid-reader-writer-module-13-56mhz-spi-kit-for-arduino
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/0-96-i2c-blue-oled-display-module-4-pin-ssd1306
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

const int RST_PIN = 9, SS_PIN = 10, SERVO_PIN = 6;
MFRC522 rfid(SS_PIN, RST_PIN);
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
Servo lock;

// Replace with the UID(s) of your authorized cards
const byte AUTHORIZED[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF}
};

void msg(const char* line1, const char* line2) {
  oled.clearDisplay();
  oled.setTextSize(2); oled.setTextColor(SSD1306_WHITE);
  oled.setCursor(0, 8);  oled.println(line1);
  oled.setCursor(0, 36); oled.println(line2);
  oled.display();
}

void setup() {
  Serial.begin(9600);
  SPI.begin(); rfid.PCD_Init();
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  lock.attach(SERVO_PIN); lock.write(0);
  msg("ShillehTek", "Tap card...");
}

bool isAuthorized(byte* uid) {
  for (auto& tag : AUTHORIZED) {
    if (memcmp(uid, tag, 4) == 0) return true;
  }
  return false;
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) return;

  if (isAuthorized(rfid.uid.uidByte)) {
    msg("ACCESS", "GRANTED");
    lock.write(90); delay(3000); lock.write(0);
  } else {
    msg("ACCESS", "DENIED");
    delay(2000);
  }
  msg("ShillehTek", "Tap card...");
  rfid.PICC_HaltA(); rfid.PCD_StopCrypto1();
}
