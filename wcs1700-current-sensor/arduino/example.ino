// Reads the WCS1700 analog output on an Arduino, calibrates a zero-offset, computes current in amps, and reports an overcurrent alarm via the digital output.
//
// Buy this module: https://shillehtek.com/products/wcs1700-70a-hall-current-sensor-module-overcurrent-detect
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/wcs1700-70a-hall-current-sensor-module-overcurrent-detect-manual
// More examples: https://github.com/shillehtek/examples
//

// WCS1700 - Read current in amps on Arduino
// Wire the load conductor through the WCS1700 hole.
// Aout to A0, Dout (optional) to D2.

const int aoutPin = A0;
const int doutPin = 2;

const float VREF        = 5.0;     // Arduino ADC reference
const float SENSITIVITY = 0.032;   // ~32 mV per amp
float       offsetVolts = 2.5;     // calibrated below

void calibrateZero() {
  long sum = 0;
  for (int i = 0; i < 200; i++) { sum += analogRead(aoutPin); delay(2); }
  offsetVolts = (sum / 200.0) * VREF / 1023.0;
}

void setup() {
  Serial.begin(9600);
  pinMode(doutPin, INPUT);
  delay(500);
  calibrateZero();
  Serial.print("Zero offset: "); Serial.print(offsetVolts, 3); Serial.println(" V");
}

void loop() {
  int raw = analogRead(aoutPin);
  float volts = raw * VREF / 1023.0;
  float amps  = (volts - offsetVolts) / SENSITIVITY;

  Serial.print("V="); Serial.print(volts, 3);
  Serial.print("V  I="); Serial.print(amps, 2); Serial.print(" A");
  if (digitalRead(doutPin) == LOW) Serial.print("  [ALARM]");
  Serial.println();
  delay(250);
}
