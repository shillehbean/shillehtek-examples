// Reads the MQ-135 analog pin and prints the raw ADC value and corresponding voltage to Serial once per second, with an initial warm-up message.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-mq135-indoor-air-monitoring
// Parts used: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int MQ_PIN = A0;

void setup() {
  Serial.begin(9600);
  Serial.println("MQ-135 warming up... readings drift for 24 h.");
}

void loop() {
  int raw = analogRead(MQ_PIN);
  // Higher voltage = more pollution (lower sensor resistance).
  Serial.print("Raw="); Serial.print(raw);
  Serial.print("  V="); Serial.println(raw * (5.0 / 1023.0), 2);
  delay(1000);
}
