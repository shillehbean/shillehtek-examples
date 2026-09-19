// Reads distance from an HC-SR04 and moves a servo to actuate a sanitizer pump when a hand is detected, ensuring one pump per hand and printing distances over Serial.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-hc-sr04-servo-touchless-sanitizer-dispenser
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

const int TRIG = 10, ECHO = 11, SERVO_PIN = 9;
const int TRIGGER_CM = 10;          // a hand closer than this dispenses
const int REST = 0, PRESS = 90;     // angles found with the servo tester
Servo arm;

long readCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 25000);    // time out if nothing is in range
  return (us == 0) ? 999 : us * 0.034 / 2; // 999 = nothing there
}

void setup() {
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  arm.attach(SERVO_PIN);
  arm.write(REST);
  Serial.begin(9600);
}

void loop() {
  long cm = readCm();
  Serial.println(cm);

  if (cm > 2 && cm < TRIGGER_CM) {         // hand detected
    arm.write(PRESS);  delay(600);           // push the pump
    arm.write(REST);   delay(400);           // let it spring back

    while (readCm() < TRIGGER_CM) delay(100);  // wait until the hand leaves
    delay(500);                                // so one wave = exactly one pump
  }
  delay(100);
}
