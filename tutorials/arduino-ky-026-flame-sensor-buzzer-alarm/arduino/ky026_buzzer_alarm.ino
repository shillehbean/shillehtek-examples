// Arduino sketch that reads the analog value from the KY-026 flame sensor on A0, prints the value to serial, and toggles a buzzer on digital pin 11 when a flame is detected (analog value < 500).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ky-026-flame-sensor-buzzer-alarm
// Parts used: https://shillehtek.com/products/flame-sensor-ky-026-arduino-esp32-raspberry-pi
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

int buzzer = 11;      // buzzer pin
int valorSensor = 0;  // value coming from the sensor

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Read the flame sensor's analog value
  valorSensor = analogRead(A0);
  Serial.println(valorSensor);

  // Sound the alarm when a flame is detected
  if (valorSensor < 500) {
    digitalWrite(buzzer, HIGH);
    delay(100);
    digitalWrite(buzzer, LOW);
    delay(50);
  }
}
