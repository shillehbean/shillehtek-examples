// Arduino Nano sketch that reads the ADC with a trigger, captures 128-sample waveforms, and displays a triggered oscilloscope trace plus Vpp and frequency on an SSD1306 OLED.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-oled-oscilloscope-30khz-waveforms
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/0-96-i2c-white-oled-display-module-4-pin-ssd1306
//             https://shillehtek.com/products/200pcs-6mm-light-touch-button-switch-kit-plastic-box-4-3-5-6-7-8-9-10-12-14-16mm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
Adafruit_SSD1306 oled(128, 64, &Wire, -1);

const int BTN_FAST = 8, BTN_SLOW = 9, BTN_HOLD = 10;
const int N = 128;                       // one sample per pixel column
uint8_t buf[N];
// microseconds per sample for each timebase, and the ADC prescaler that gives it
const unsigned int STEP_US[7] = {13, 26, 52, 104, 250, 1000, 5000};
const uint8_t      PRESC[7]   = {4,  5,  6,  7,   7,   7,    7};     // 16, 32, 64, 128 ...
int tb = 3; bool hold = false;
float vpp = 0, freq = 0;

inline uint8_t sample() {                // 8-bit read, left-adjusted result in ADCH
  ADCSRA |= (1 << ADSC); while (ADCSRA & (1 << ADSC)); return ADCH;
}

void capture() {
  ADCSRA = (1 << ADEN) | PRESC[tb];       // ADC on, speed set by the timebase
  bool armed = false; unsigned long t0 = micros();
  while (micros() - t0 < 20000) {         // trigger: rising edge through mid-scale, 20 ms timeout
    uint8_t v = sample();
    if (v < 110) armed = true;
    else if (armed && v >= 128) break;
  }
  for (int i = 0; i < N; i++) {
    if (tb < 4) buf[i] = sample();                          // fast ranges: as quick as the ADC allows
    else { unsigned long t = micros(); buf[i] = sample(); while (micros() - t < STEP_US[tb]) {} }
  }
}

void measure() {
  uint8_t lo = 255, hi = 0; int crossings = 0, first = -1, last = -1; bool below = buf[0] < 118;
  for (int i = 0; i < N; i++) {
    lo = min(lo, buf[i]); hi = max(hi, buf[i]);
    if (below && buf[i] >= 138) { below = false; crossings++; if (first < 0) first = i; last = i; }
    else if (!below && buf[i] < 118) below = true;
  }
  vpp = (hi - lo) * 5.0 / 255.0;
  float span = (last - first) * (STEP_US[tb] * 1e-6);            // seconds between first and last edge
  freq = (crossings >= 2) ? (crossings - 1) / span : 0;
}

void draw() {
  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.print((unsigned long)STEP_US[tb] * 16); oled.print("us ");   // per 16-pixel division
  oled.print(vpp, 2); oled.print("V ");
  if (freq >= 1000) { oled.print(freq / 1000, 1); oled.print("kHz"); }
  else              { oled.print(freq, 0);        oled.print("Hz"); }
  if (hold) oled.print(" H");
  for (int x = 0; x < 128; x += 16) for (int y = 12; y < 64; y += 4) oled.drawPixel(x, y, SSD1306_WHITE);   // grid
  for (int i = 1; i < N; i++)
    oled.drawLine(i - 1, 63 - buf[i - 1] * 51 / 255, i, 63 - buf[i] * 51 / 255, SSD1306_WHITE);
  oled.display();
}

void setup() {
  pinMode(BTN_FAST, INPUT_PULLUP); pinMode(BTN_SLOW, INPUT_PULLUP); pinMode(BTN_HOLD, INPUT_PULLUP);
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); oled.setTextColor(SSD1306_WHITE);
  ADMUX = (1 << REFS0) | (1 << ADLAR);    // AVcc reference, left-adjust, channel A0
  analogWrite(5, 128);                    // built-in test signal: 980 Hz square wave on D5
}

void loop() {
  if (!digitalRead(BTN_FAST) && tb > 0) { tb--; delay(200); }
  if (!digitalRead(BTN_SLOW) && tb < 6) { tb++; delay(200); }
  if (!digitalRead(BTN_HOLD)) { hold = !hold; delay(300); }
  if (!hold) { capture(); measure(); }
  draw();
}
