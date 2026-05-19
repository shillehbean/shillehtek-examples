// Implements a USB media control remote using the HID-Project library, mapping three buttons (D2/D3/D4) to Play/Pause, Next, and Previous commands.
//
// Buy this module: https://shillehtek.com/products/manual
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pro-micro-atmega32u4-5v-16mhz-presoldered-type-c-manual
// More examples: https://github.com/shillehtek/examples
//

// Turns the Pro Micro into a media control remote.
// Requires the HID-Project library (install via Library Manager).
// Wire three buttons: D2=Play/Pause, D3=Next, D4=Previous.

#include <HID-Project.h>

const int PLAY_PIN = 2;
const int NEXT_PIN = 3;
const int PREV_PIN = 4;

void setup() {
  pinMode(PLAY_PIN, INPUT_PULLUP);
  pinMode(NEXT_PIN, INPUT_PULLUP);
  pinMode(PREV_PIN, INPUT_PULLUP);
  Consumer.begin();
}

void loop() {
  if (digitalRead(PLAY_PIN) == LOW) {
    Consumer.write(MEDIA_PLAY_PAUSE);
    delay(200);
  }
  if (digitalRead(NEXT_PIN) == LOW) {
    Consumer.write(MEDIA_NEXT);
    delay(200);
  }
  if (digitalRead(PREV_PIN) == LOW) {
    Consumer.write(MEDIA_PREVIOUS);
    delay(200);
  }
}
