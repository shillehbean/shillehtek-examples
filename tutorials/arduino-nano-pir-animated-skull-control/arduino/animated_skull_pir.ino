// Arduino sketch that reads an HC-SR501 PIR sensor and, on motion, animates a servo jaw while flashing LED eyes and playing a buzzer tone.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-pir-animated-skull-control
// Parts used: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>
const int PIR = 2, BUZZ = 8;
const int LED_L = 5, LED_R = 6;
Servo jaw;
void setup() {
  pinMode(PIR, INPUT);
  pinMode(BUZZ, OUTPUT);
  pinMode(LED_L, OUTPUT); pinMode(LED_R, OUTPUT);
  jaw.attach(9); jaw.write(0);
}
void scare() {
  for (int i = 0; i < 8; i++) {
    jaw.write(40); analogWrite(LED_L, 255); analogWrite(LED_R, 255);
    tone(BUZZ, 300 + random(200));
    delay(100);
    jaw.write(0);  analogWrite(LED_L, 60); analogWrite(LED_R, 60);
    delay(80);
  }
  noTone(BUZZ);
}
void loop() {
  if (digitalRead(PIR) == HIGH) {
    scare();
    delay(5000);   // 5s cooldown
  }
}
