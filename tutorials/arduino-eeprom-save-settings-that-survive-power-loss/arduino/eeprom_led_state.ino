// Arduino sketch that toggles an LED with a pushbutton and saves/restores the LED state in EEPROM using EEPROM.update so the state survives power loss.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-eeprom-save-settings-that-survive-power-loss
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <EEPROM.h>
const int BTN = 10, LED = 13, ADDR = 0;
bool state;

void setup() {
  pinMode(BTN, INPUT_PULLUP); pinMode(LED, OUTPUT);
  state = EEPROM.read(ADDR) == 1;     // restore last state (blank EEPROM reads 255 = off)
  digitalWrite(LED, state);
}

void loop() {
  if (digitalRead(BTN) == LOW) {
    state = !state;
    digitalWrite(LED, state);
    EEPROM.update(ADDR, state ? 1 : 0);   // save only if it changed
    delay(300);                           // crude debounce
  }
}
