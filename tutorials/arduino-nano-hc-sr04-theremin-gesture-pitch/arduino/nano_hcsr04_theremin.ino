// Reads distance from an HC-SR04 ultrasonic sensor and plays a mapped pitch on a piezo buzzer (theremin-style).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-hc-sr04-theremin-gesture-pitch
// Parts used: https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int TRIG = 9, ECHO = 10;
const int BUZZ = 8;
void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}
void loop() {
  digitalWrite(TRIG, LOW); delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);
  if (us > 0 && us < 20000) {
    long cm = us * 0.0343 / 2.0;
    // Map 5-50cm to a 200-2000Hz tone range
    int freq = map(cm, 5, 50, 2000, 200);
    tone(BUZZ, freq);
  } else {
    noTone(BUZZ);
  }
  delay(50);
}
