// Simple Arduino Leonardo/Pro Micro sketch that reads two foot-pedal switches on pins D2 and D3 and sends Page Down / Page Up USB HID keystrokes when pressed.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-leonardo-usb-hid-foot-pedal-keyboard
// Parts used: https://shillehtek.com/products/arduino-leonardo-r3-atmega32u4
//             https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-pre-soldered-usb-c-development-board
//             https://shillehtek.com/products/micro-usb-cable-0-5m-1-64ft
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include "Keyboard.h"

#define PEDAL1_PIN 2
#define PEDAL2_PIN 3

// Works on ATmega32U4 boards (Leonardo/Pro Micro) - native USB HID

static void Pedal1Down(void)
{
  Keyboard.press(KEY_PAGE_DOWN);
}

static void Pedal2Down(void)
{
  Keyboard.press(KEY_PAGE_UP);
}

void setup(void)
{
  Keyboard.begin();

  pinMode(PEDAL1_PIN, INPUT);
  digitalWrite(PEDAL1_PIN, HIGH); // enable pull-up

  pinMode(PEDAL2_PIN, INPUT);
  digitalWrite(PEDAL2_PIN, HIGH); // enable pull-up
}

void loop(void)
{
  static uint8_t pedal1StateLast = 0;
  static uint8_t pedal2StateLast = 0;
  uint8_t pedalState;

  pedalState = digitalRead(PEDAL1_PIN);
  if (pedalState != pedal1StateLast) {
    pedal1StateLast = pedalState;
    if (pedalState == 0) {
      Pedal1Down();
      delay(100);
      Keyboard.releaseAll();
    }
  }

  pedalState = digitalRead(PEDAL2_PIN);
  if (pedalState != pedal2StateLast) {
    pedal2StateLast = pedalState;
    if (pedalState == 0) {
      Pedal2Down();
      delay(100);
      Keyboard.releaseAll();
    }
  }

  delay(50);
}
