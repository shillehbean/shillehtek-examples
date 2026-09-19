// Arduino sketch demonstrating storing a Settings struct in EEPROM with a magic marker and boot counter, loading defaults if absent, and updating settings from Serial input (snippet is truncated).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-eeprom-save-settings-that-survive-power-loss
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <EEPROM.h>

struct Settings {
  uint16_t magic;        // 0xCAFE means "these are valid"
  uint16_t boots;        // how many times the board has started
  int      threshold;    // e.g. an alarm level
  float    calOffset;    // e.g. a sensor correction
  bool     ledOn;
};
const uint16_t MAGIC = 0xCAFE;
const int ADDR = 0;
Settings cfg;

void save() { EEPROM.put(ADDR, cfg); }     // writes only bytes that changed

void load() {
  EEPROM.get(ADDR, cfg);
  if (cfg.magic != MAGIC) {                // first boot (or corrupted): defaults
    cfg = { MAGIC, 0, 500, 0.0, false };
    save();
  }
}

void setup() {
  Serial.begin(9600);
  load();
  cfg.boots++;                             // count this start-up
  save();
  Serial.print("boot #"); Serial.println(cfg.boots);
  Serial.print("threshold "); Serial.println(cfg.threshold);
  Serial.print("calOffset "); Serial.println(cfg.calOffset, 3);
}

void loop() {
  // change a setting from the Serial Monitor: type  t=700  or  c=1.25
  if (Serial.available()) {
    String s = Serial.readStringUntil('\n'); s.trim();
    if (s.startsWith("t=")) cfg.threshold = s.substring(2).toInt();
    if (s.startsWith("c=")) cfg.calOffset = s.substring(2).toFloat();
    save();
    Serial.println("saved");
  }
}
