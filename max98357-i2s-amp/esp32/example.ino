// Generate and stream a 440 Hz sine-wave stereo I2S signal from an ESP32 to the MAX98357 amplifier.
//
// Buy this module: https://shillehtek.com/products/max98357-i2s-class-d-amplifier-module-pre-soldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max98357-i2s-class-d-amplifier-module-pre-soldered-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MAX98357 I2S amplifier - 440 Hz sine test tone from an ESP32
// Needs the ESP32 board package 3.0 or newer, which provides ESP_I2S.h
// Wiring: VIN = 5V, GND = GND, BCLK = GPIO 26, LRC = GPIO 25, DIN = GPIO 22
#include <ESP_I2S.h>

const int PIN_BCLK = 26;
const int PIN_LRC  = 25;
const int PIN_DIN  = 22;

const int sampleRate  = 44100;     // samples per second
const float frequency = 440.0;     // tone pitch in Hz
const int amplitude   = 4000;      // volume, up to 32767

I2SClass i2s;
int16_t samples[512];              // 256 stereo frames: left, right, left, right ...
float phase = 0.0;

void setup() {
  Serial.begin(115200);
  i2s.setPins(PIN_BCLK, PIN_LRC, PIN_DIN);
  if (!i2s.begin(I2S_MODE_STD, sampleRate, I2S_DATA_BIT_WIDTH_16BIT, I2S_SLOT_MODE_STEREO)) {
    Serial.println("Failed to start I2S");
    while (true) { delay(1000); }
  }
}

void loop() {
  const float step = 2.0 * PI * frequency / sampleRate;
  for (int i = 0; i < 256; i++) {
    int16_t value = (int16_t)(amplitude * sin(phase));
    samples[2 * i] = value;          // left channel
    samples[2 * i + 1] = value;      // right channel
    phase += step;
    if (phase >= 2.0 * PI) phase -= 2.0 * PI;
  }
  i2s.write((uint8_t *)samples, sizeof(samples));   // waits until the samples are queued
}
