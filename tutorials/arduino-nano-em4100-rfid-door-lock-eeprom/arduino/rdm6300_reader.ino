// Reads RDM6300 125 kHz RFID serial packets over SoftwareSerial and prints the 10-character card ID to the Serial monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-em4100-rfid-door-lock-eeprom
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-12v-relay-module
//             https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>
SoftwareSerial rfid(2, 3);  // RX, TX

void setup() {
  Serial.begin(9600);
  rfid.begin(9600);
}

void loop() {
  if (rfid.available() >= 14) {
    if (rfid.read() == 0x02) {
      char id[11] = {0};
      for (int i = 0; i < 10; i++) id[i] = rfid.read();
      Serial.print("ID: "); Serial.println(id);
      while (rfid.available()) rfid.read();   // flush
    }
  }
}
