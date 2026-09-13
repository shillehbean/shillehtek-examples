// Main loop that reads RFID tags, uses the EEPROM authorization helper, and drives the lock relay and OK/FAIL LEDs to unlock/relock or indicate denial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-em4100-rfid-door-lock-eeprom
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-12v-relay-module
//             https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LOCK_RELAY = 7;
const int OK_LED     = 8;
const int FAIL_LED   = 9;
const unsigned long UNLOCK_MS = 5000;

void loop() {
  if (rfid.available() >= 14 && rfid.read() == 0x02) {
    char id[11] = {0};
    for (int i = 0; i < 10; i++) id[i] = rfid.read();
    while (rfid.available()) rfid.read();
    if (isAuthorized(id)) {
      digitalWrite(LOCK_RELAY, LOW);    // unlock
      digitalWrite(OK_LED, HIGH);
      delay(UNLOCK_MS);
      digitalWrite(LOCK_RELAY, HIGH);   // re-lock
      digitalWrite(OK_LED, LOW);
    } else {
      digitalWrite(FAIL_LED, HIGH);
      delay(1000);
      digitalWrite(FAIL_LED, LOW);
    }
  }
}
