// Arduino sketch that powers a laser, reads an LDR sensor via analog input, and sounds a buzzer when the LDR reading falls below a configurable threshold (beam broken).
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-laser-diode-tripwire-alarm
// Parts used: https://shillehtek.com/products/shillehtek-6mm-650nm-5mw-red-laser-diode-module
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LASER = 7;
const int LDR = A0;
const int BUZZER = 8;
const int THRESHOLD = 300;   // tune for your room

void setup() {
  pinMode(LASER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  digitalWrite(LASER, HIGH);
  Serial.begin(9600);
}

void loop() {
  int v = analogRead(LDR);
  Serial.println(v);
  if (v < THRESHOLD) {
    tone(BUZZER, 1000);      // beam broken!
  } else {
    noTone(BUZZER);
  }
  delay(50);
}
