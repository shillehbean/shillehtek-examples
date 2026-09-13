// Reads the MQ-135 sensor on analog pin A0 and prints the raw ADC value to the Serial Monitor every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-mq135-read-serial-monitor-values
// Parts used: https://shillehtek.com/products/mq-135-air-quality-hazardous-gas-sensor-module-for-arduino
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define MQ135_PIN A0

void setup() {
  Serial.begin(115200);
}

void loop() {
  int rawValue = analogRead(MQ135_PIN);

  Serial.print("MQ135 Analog Value: ");
  Serial.println(rawValue);

  delay(1000);
}
