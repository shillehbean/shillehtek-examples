// Simple example that reads the analog voltage on A0 and prints the raw ADC value to the Serial console every 100 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-mq-7-co-buzzer-alarm
// Parts used: https://shillehtek.com/products/mq-7-co-gas-sensor-module-arduino-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ds18b20-waterproof-digital-temp-sensor-probe-1m-for-arduino-pi
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// AnalogReadSerial - reads A0 and prints to Serial
// (File  Examples  01.Basics  AnalogReadSerial)

void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  delay(100);
}
