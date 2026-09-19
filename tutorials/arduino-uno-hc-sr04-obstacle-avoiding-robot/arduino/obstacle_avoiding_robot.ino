// Arduino sketch that initializes the HC-SR04 and servo, reads distances, and provides motor-control functions to drive an obstacle-avoiding robot.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hc-sr04-obstacle-avoiding-robot
// Parts used: https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
//             https://shillehtek.com/products/n20-micro-metal-gear-motor-12v-100rpm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>

const int TRIG = 9, ECHO = 10, SERVO_PIN = 3;
const int L_FWD = 5, L_REV = 4, R_FWD = 7, R_REV = 6;
const int STOP_CM = 20;
Servo head;

long readCm() {
  digitalWrite(TRIG, LOW);  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH); delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long us = pulseIn(ECHO, HIGH, 25000);
  return us == 0 ? 400 : us * 0.034 / 2;          // no echo = treat as far away
}

void drive(bool lf, bool lr, bool rf, bool rr) {  // one function for every motion
  digitalWrite(L_FWD, lf); digitalWrite(L_REV, lr);
  digitalWrite(R_FWD, rf); digitalWrite(R_REV, rr);
}
void forward()  { drive(1, 0, 1, 0); }
void backward() { drive(0, 1, 0, 1); }
void left()     { drive(0, 1, 1, 0); }            // spin in place
void right()    { drive(1, 0, 0, 1); }
void stopAll()  { drive(0, 0, 0, 0); }

long lookAt(int angle) {                          // aim the sensor, settle, measure
  head.write(angle); delay(350);
  long d = readCm(); head.write(90); return d;
}

void setup() {
  pinMode(TRIG, OUTPUT); pinMode(ECHO, INPUT);
  for (int p : {L_FWD, L_REV, R_FWD, R_REV}) pinMode(p, OUTPUT);
  head.attach(SERVO_PIN); head.write(90);
  delay(1000);                                    // a second to put it down
}

void loop() {
  long ahead = readCm();
  if (ahead > STOP_CM) { forward(); delay(50); return; }

  stopAll(); delay(200);                          // obstacle: back off and look around
  backward(); delay(400); stopAll(); delay(200);
  long leftCm = lookAt(160), rightCm = lookAt(20);
  if (leftCm > rightCm) left(); else right();
  delay(450);                                     // ~90 degrees; tune for your chassis
  stopAll(); delay(100);
}
