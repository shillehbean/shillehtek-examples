// Arduino sketch for a Pro Micro that sends MIDI Note On/Off for 8 buttons and MIDI CC messages for 4 potentiometers over USB using the MIDIUSB library.
//
// Full tutorial: https://shillehtek.com/blogs/news/pro-micro-buttons-pots-usb-midi-build
// Parts used: https://shillehtek.com/products/pro-micro-atmega32u4-5v-16mhz-presoldered-micro-usb
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <MIDIUSB.h>
const int BTN_PINS[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int POT_PINS[] = {A0, A1, A2, A3};
bool prev[8];
int lastPot[4];
void noteOn(byte note) {
  midiEventPacket_t e = {0x09, 0x90, note, 100};
  MidiUSB.sendMIDI(e); MidiUSB.flush();
}
void noteOff(byte note) {
  midiEventPacket_t e = {0x08, 0x80, note, 0};
  MidiUSB.sendMIDI(e); MidiUSB.flush();
}
void cc(byte ctl, byte val) {
  midiEventPacket_t e = {0x0B, 0xB0, ctl, val};
  MidiUSB.sendMIDI(e); MidiUSB.flush();
}
void setup() {
  for (int p : BTN_PINS) pinMode(p, INPUT_PULLUP);
}
void loop() {
  for (int i = 0; i < 8; i++) {
    bool now = digitalRead(BTN_PINS[i]) == LOW;
    if (now && !prev[i]) noteOn(60 + i);
    if (!now && prev[i]) noteOff(60 + i);
    prev[i] = now;
  }
  for (int i = 0; i < 4; i++) {
    int v = analogRead(POT_PINS[i]) >> 3;   // 0-127 MIDI range
    if (abs(v - lastPot[i]) > 1) {
      cc(20 + i, v); lastPot[i] = v;
    }
  }
  delay(5);
}
