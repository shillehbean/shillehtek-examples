// Reads the MQ-7 analog output (A0) and digital threshold (DO) on an Arduino, printing the raw ADC value, the computed 0–5V sensor voltage, and whether the digital threshold is exceeded.
//
// Buy this module: https://shillehtek.com/products/mq-7-co-gas-sensor-module-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mq-7-co-gas-sensor-module-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int AO_PIN = A0;
const int DO_PIN = 2;

void setup() {
  Serial.begin(9600);
  pinMode(DO_PIN, INPUT);
  Serial.println("MQ-7 warming up (give it several minutes)...");
}

void loop() {
  int raw = analogRead(AO_PIN);
  float voltage = raw * (5.0 / 1023.0);
  bool alarm = digitalRead(DO_PIN) == LOW;  // LOW = threshold crossed

  Serial.print("Raw: ");
  Serial.print(raw);
  Serial.print("  Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V  Threshold: ");
  Serial.println(alarm ? "EXCEEDED" : "ok");
  delay(1000);
}
