// Outputs a continuous ~1 kHz sine wave from the ESP32 DAC on GPIO25 (DAC1) via a 1 µF coupling capacitor to the TPA3118's Audio IN+ by sending voltage samples at ~8 kHz.
//
// Buy this module: https://shillehtek.com/products/tpa3118-pbtl-single-digital-amplifier-board-1x60w
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tpa3118-pbtl-single-digital-amplifier-board-1x60w-manual
// More examples: https://github.com/shillehtek/examples
//

// ESP32 - DAC sine wave through TPA3118
// GPIO 25 (DAC1) -- 1uF cap -- Audio IN+

#include <math.h>
#include <driver/dac.h>

void setup() {
  dac_output_enable(DAC_CHANNEL_1);  // GPIO 25
}

void loop() {
  static float phase = 0;
  float sample = sin(phase) * 0.5 + 0.5;     // 0..1
  dac_output_voltage(DAC_CHANNEL_1, (uint8_t)(sample * 255));
  phase += 2 * PI * 1000.0 / 8000.0;          // 1 kHz at 8 kHz sample rate
  if (phase > 2 * PI) phase -= 2 * PI;
  delayMicroseconds(125);
}
