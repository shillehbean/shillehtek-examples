// Reads distance from an HC-SR04 and controls a servo to open the dustbin lid when an object is detected, keeping it open for a set hold time and moving the servo slowly to avoid slamming.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hc-sr04-touchless-dustbin-lid
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
//             https://shillehtek.com/products/servo-tester-rc-ccpm-checker
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

const int TRIG = 10, ECHO = 11, SERVO_PIN = 9;
const int CLOSED = 0, OPEN = 100;          // angles from the servo tester
const int TRIGGER_CM = 30;                 // hand closer than this opens the lid
const unsigned long HOLD_MS = 3000;        // stay open this long after the hand leaves
Servo lid;
bool isOpen = false;
unsigned long lastSeen = 0;

long readCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 25000);
  return us == 0 ? 999 : us * 0.034 / 2;
}

void moveLid(int from, int to) {            // sweep slowly so the lid doesn't slam
  int step = (to > from) ? 2 : -2;
  for (int a = from; a != to; a += step) { lid.write(a); delay(8); }
  lid.write(to);
}

void setup() {
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  lid.attach(SERVO_PIN); lid.write(CLOSED);
  Serial.begin(9600);
}

void loop() {
  long cm = readCm();
  if (cm > 2 && cm < TRIGGER_CM) {          // something is in front of the bin
    lastSeen = millis();
    if (!isOpen) { moveLid(CLOSED, OPEN); isOpen = true; }
  }
  if (isOpen && millis() - lastSeen > HOLD_MS) {   // clear for 3 s: close
    moveLid(OPEN, CLOSED); isOpen = false;
  }
  delay(60);
}
