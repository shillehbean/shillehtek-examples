// Plays a 440 Hz square-wave test tone over I2S (stereo) using Arduino's I2S library on SAMD21 boards to drive the PCM5102 DAC.
//
// Buy this module: https://shillehtek.com/products/pcm5102-i2s-stereo-dac-presoldered-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/pcm5102-i2s-stereo-dac-presoldered-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// PCM5102 I2S DAC - 440 Hz test tone from an I2S-capable Arduino
// For SAMD21 boards (Nano 33 IoT, MKR family, Zero). The Uno and classic Nano have no I2S.
// Wiring: LCK = A2 (Nano 33 IoT), 3 (MKR) or 0 (Zero)
//         BCK = A3 (Nano 33 IoT), 2 (MKR) or 1 (Zero)
//         DIN = 4 (Nano 33 IoT), A6 (MKR) or 9 (Zero)
//         VIN = 3.3V, GND = GND, SCK = GND
#include <I2S.h>

const int sampleRate = 8000;       // samples per second
const int frequency  = 440;        // tone pitch in Hz
const int amplitude  = 2000;       // volume, up to 32767
const int halfWave   = sampleRate / frequency / 2;   // samples per half wave

short sample = amplitude;
int count = 0;

void setup() {
  Serial.begin(115200);
  if (!I2S.begin(I2S_PHILIPS_MODE, sampleRate, 16)) {
    Serial.println("Failed to start I2S");
    while (true) { delay(1000); }
  }
}

void loop() {
  if (count % halfWave == 0) {
    sample = -sample;                // flip the square wave
  }
  I2S.write(sample);                 // left channel
  I2S.write(sample);                 // right channel
  count++;
}
