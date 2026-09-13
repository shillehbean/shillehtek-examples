// Triggers an HC-SR04 ultrasonic sensor and prints live distance measurements in centimetres to the Serial Monitor at 9600 baud.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hc-sr04-serial-distance-monitor
// Parts used: https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int TRIG = 9;
const int ECHO = 10;

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  long us = pulseIn(ECHO, HIGH);
  float cm = us * 0.0343 / 2.0;   // speed of sound 343 m/s
  Serial.print("Distance: ");
  Serial.print(cm, 1);
  Serial.println(" cm");
  delay(200);
}
