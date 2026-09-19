// Measures pulses from a Colpitts oscillator with FreqCount, maintains a running baseline, and controls LEDs and a buzzer to indicate frequency deviations caused by nearby metal.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-colpitts-frequency-counting-metal-detector
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
//             https://shillehtek.com/products/200pcs-electrolytic-capacitors-0-1uf-50v-220uf-10v-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <FreqCount.h>

const int BUZZ = 12, BLUE = A2, GREEN = A4, RED = A5;
long baseline = 0;

void setup() {
  pinMode(BUZZ, OUTPUT);
  pinMode(BLUE, OUTPUT); pinMode(GREEN, OUTPUT); pinMode(RED, OUTPUT);
  FreqCount.begin(100);              // count pulses per 100 ms on D5
}

void loop() {
  if (!FreqCount.available()) return;
  long f = FreqCount.read();

  if (baseline == 0) baseline = f;   // first reading
  long diff = abs(f - baseline);

  digitalWrite(BLUE,  diff <= 1);             // quiet: on target baseline
  digitalWrite(GREEN, diff > 1 && diff <= 5); // small shift: metal near
  digitalWrite(RED,   diff > 5);              // big shift: metal HERE

  if (diff > 5) tone(BUZZ, 800 + diff * 20, 90);   // pitch tracks strength

  baseline = (baseline * 15 + f) / 16;  // slow auto-recalibration
}
