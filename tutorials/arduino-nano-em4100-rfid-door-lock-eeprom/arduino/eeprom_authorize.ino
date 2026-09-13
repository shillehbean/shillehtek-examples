// Checks a 10-character card ID against up to MAX_CARDS stored entries in the AVR EEPROM and returns whether it's authorized.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-em4100-rfid-door-lock-eeprom
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-channel-12v-relay-module
//             https://shillehtek.com/products/4-bits-tm1637-red-led-display-module-clock
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <EEPROM.h>
const int MAX_CARDS = 10;

bool isAuthorized(const char* id) {
  for (int i = 0; i < MAX_CARDS; i++) {
    char stored[11] = {0};
    for (int j = 0; j < 10; j++)
      stored[j] = EEPROM.read(i * 10 + j);
    if (strncmp(stored, id, 10) == 0) return true;
  }
  return false;
}
