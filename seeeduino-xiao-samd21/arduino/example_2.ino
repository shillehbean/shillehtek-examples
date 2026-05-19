// Outputs a 100-sample 10-bit sine wave on the DAC pin (A0/D0) using a lookup table and timed writes to produce an analog waveform.
//
// Buy this module: https://shillehtek.com/products/seeeduino-xiao-samd21-arduino-board-presoldered
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/seeeduino-xiao-samd21-arduino-board-presoldered-manual
// More examples: https://github.com/shillehtek/examples
//

// Seeeduino XIAO SAMD21 - Generate a sine wave on the DAC (D0 / A0)
// The SAMD21 has a true 10-bit DAC (0-1023 maps to 0-3.3V)

#include <math.h>

const int dacPin = A0;   // D0 / A0 is the DAC output
const int samples = 100;
int wave[samples];

void setup() {
  analogWriteResolution(10);   // 10-bit DAC
  for (int i = 0; i < samples; i++) {
    wave[i] = int(512.0 + 511.0 * sin(2.0 * M_PI * i / samples));
  }
}

void loop() {
  for (int i = 0; i < samples; i++) {
    analogWrite(dacPin, wave[i]);
    delayMicroseconds(50);
  }
}
