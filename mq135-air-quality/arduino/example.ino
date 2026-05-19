// Reads the MQ-135 analog output on A0 and the digital alarm on D2, printing raw ADC, computed voltage, and the DO alarm state to Serial at 9600 baud every 0.5s.
//
// Buy this module: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// MQ-135 - Print analog air quality reading on Arduino
// Allow 1-3 minutes warm-up after powering on for stable values.

const int aoPin = A0;
const int doPin = 2;

void setup() {
  Serial.begin(9600);
  pinMode(doPin, INPUT);
  Serial.println("MQ-135 warming up... wait at least 1 minute.");
}

void loop() {
  int raw = analogRead(aoPin);
  float volts = raw * 5.0 / 1023.0;

  Serial.print("Raw=");   Serial.print(raw);
  Serial.print("  V=");   Serial.print(volts, 2);
  Serial.print("  DO=");  Serial.print(digitalRead(doPin));
  if (digitalRead(doPin) == LOW) Serial.print("  [ALARM]");
  Serial.println();

  delay(500);
}
