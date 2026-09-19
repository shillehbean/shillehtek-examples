// Initializes the SH1106 OLED, input buttons, RGB LED pins, and DFPlayer Mini over SoftwareSerial, then restores volume, EQ, and last-played track from EEPROM.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-dfplayer-mini-oled-mp3-player
// Parts used: https://shillehtek.com/products/mp3-player-module-tf-card-arduino-raspberry-pi
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/1-3-i2c-blue-oled-display-module-4-pin-sh1106
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>
#include <U8g2lib.h>
#include <Wire.h>
#include <EEPROM.h>

#define BTN_PREV   2    // interrupt pin
#define BTN_NEXT   3    // interrupt pin
#define BTN_SELECT 5
#define LED_R 11
#define LED_G 10
#define LED_B 6

SoftwareSerial mp3Serial(12, 13);   // RX, TX
DFRobotDFPlayerMini player;
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

void setup() {
  u8g2.begin();
  pinMode(BTN_PREV, INPUT_PULLUP);
  pinMode(BTN_NEXT, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
  pinMode(LED_R, OUTPUT); pinMode(LED_G, OUTPUT); pinMode(LED_B, OUTPUT);

  mp3Serial.begin(9600);
  player.begin(mp3Serial);

  player.volume(EEPROM.read(0));        // restore saved volume (0-30)
  player.EQ(EEPROM.read(1));            // restore saved EQ preset
  player.playFolder(1, EEPROM.read(2)); // resume the last track
}
