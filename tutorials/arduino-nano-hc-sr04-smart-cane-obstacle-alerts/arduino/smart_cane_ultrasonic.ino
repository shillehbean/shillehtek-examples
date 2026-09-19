// Reads distance from an HC-SR04 ultrasonic sensor, averages readings, and drives a buzzer and vibration motor with three distance-based alert zones and a mute switch.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-hc-sr04-smart-cane-obstacle-alerts
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int TRIG = 3, ECHO = 2, BUZZ = 5, MOTOR = 6, MUTE = 7;
const int FAR_CM = 120, NEAR_CM = 60, DANGER_CM = 30;   // the three warning zones

long readCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 30000);
  return us == 0 ? 999 : us * 0.034 / 2;
}

void setup() {
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  pinMode(BUZZ, OUTPUT); pinMode(MOTOR, OUTPUT);
  pinMode(MUTE, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  long cm = 0;
  for (int i = 0; i < 3; i++) cm += readCm();   // average three pings for stability
  cm /= 3;
  bool quiet = (digitalRead(MUTE) == LOW);       // switch closed = vibration only
  Serial.println(cm);

  if (cm > FAR_CM) {                             // clear path: silence
    digitalWrite(MOTOR, LOW);
    delay(100);
    return;
  }

  // closer = shorter gap between pulses: 600 ms at 120 cm down to ~60 ms at 30 cm
  int gap = map(constrain(cm, DANGER_CM, FAR_CM), DANGER_CM, FAR_CM, 60, 600);
  int pitch = (cm < DANGER_CM) ? 2000 : (cm < NEAR_CM) ? 1200 : 800;   // zone tone

  digitalWrite(MOTOR, HIGH);
  if (!quiet) tone(BUZZ, pitch, 40);
  delay(50);
  digitalWrite(MOTOR, LOW);
  delay(gap);
}
