// Samples an analog microphone, runs an FFT on the samples, and displays frequency-band bars on a MAX7219 32x8 LED matrix.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-inmp441-max7219-spectrum-visualizer
// Parts used: https://shillehtek.com/products/inmp441-i2s-omnidirectional-microphone-module-with-soldering
//             https://shillehtek.com/products/max7219-4-in-1-dot-matrix-display-module-red
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <arduinoFFT.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define MIC_PIN A0
#define SAMPLES 64
#define MAX_DEVICES 4
double vReal[SAMPLES], vImag[SAMPLES];
arduinoFFT FFT;
MD_Parola display(MD_MAX72XX::FC16_HW, 10, MAX_DEVICES);
const int BANDS = 16;
void setup() {
  display.begin(); display.setIntensity(2); display.displayClear();
}
void loop() {
  for (int i = 0; i < SAMPLES; i++) {
    vReal[i] = analogRead(MIC_PIN) - 512;
    vImag[i] = 0;
  }
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, SAMPLES, FFT_FORWARD);
  display.displayClear();
  for (int b = 0; b < BANDS; b++) {
    int h = constrain(vReal[b + 2] / 50, 0, 8);
    // draw a vertical bar 'h' pixels tall at column b*2
    for (int y = 8 - h; y < 8; y++) {
      display.getGraphicObject()->setPoint(y, b * 2, true);
    }
  }
  display.getGraphicObject()->update();
}
