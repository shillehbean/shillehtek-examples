// Measures distance with the HC‑SR04, prints the value over Serial, and sets the onboard WS2812B RGB LEDs to colors that indicate distance ranges.
//
// Buy this module: https://shillehtek.com/products/shillehtek-hc-sr04-with-rgb-light-distance
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/shillehtek-hc-sr04-with-rgb-light-distance-manual
// More examples: https://github.com/shillehtek/examples
//

// HC-SR04 with RGB Light:
// - Trigger on D2, Echo on D3
// - RGB_IN on D6 (4 WS2812B pixels onboard)
// - Prints distance over Serial and colors LEDs by range.

#include <Adafruit_NeoPixel.h>

#define TRIG_PIN   2
#define ECHO_PIN   3
#define LED_PIN    6
#define NUM_LEDS   4

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);
  strip.begin();
  strip.setBrightness(40);  // 0-255; keep low to avoid overheating
  strip.show();
  Serial.begin(9600);
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1;  // timeout / out of range
  return duration * 0.0343f / 2.0f;
}

void setAll(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) strip.setPixelColor(i, r, g, b);
  strip.show();
}

void loop() {
  float cm = readDistanceCm();
  Serial.print("Distance: ");
  Serial.print(cm);
  Serial.println(" cm");

  if (cm < 0)        setAll(0, 0, 50);     // no echo = blue
  else if (cm < 15)  setAll(255, 0, 0);    // very close = red
  else if (cm < 50)  setAll(255, 120, 0);  // mid = orange
  else                setAll(0, 200, 0);    // far = green

  delay(80);
}
