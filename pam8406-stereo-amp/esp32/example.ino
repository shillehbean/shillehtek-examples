// Generates an 8-bit sine lookup table and outputs it on ESP32 DAC1 (GPIO25) to sweep audible tones through the PAM8406 amplifier.
//
// Buy this module: https://shillehtek.com/products/pam8406-stereo-class-d-amplifier-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pam8406-stereo-class-d-amplifier-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PAM8406 Amplifier - ESP32 Example (DAC sine sweep)
// INL -> GPIO 25 (DAC1), input GND -> GND, VCC -> VIN(5V)

#include <math.h>

const int SAMPLES = 64;
uint8_t sine[SAMPLES];

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < SAMPLES; i++) {
    sine[i] = 128 + 100 * sinf(2 * PI * i / SAMPLES);  // 8-bit sine
  }
  Serial.println("Sweeping 200 Hz - 2 kHz on DAC1...");
}

void playTone(float freq, int ms) {
  // per-sample delay in microseconds for the target frequency
  int us = (int)(1000000.0f / (freq * SAMPLES));
  long end = millis() + ms;
  int i = 0;
  while (millis() < end) {
    dacWrite(25, sine[i]);
    i = (i + 1) % SAMPLES;
    delayMicroseconds(us);
  }
}

void loop() {
  for (float f = 200; f <= 2000; f *= 1.12f) {
    playTone(f, 120);
  }
  dacWrite(25, 128);          // rest at midpoint = silence
  delay(1500);
}
