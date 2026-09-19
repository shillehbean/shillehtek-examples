// Reads two IR line sensors and controls the L298N motor driver to drive the robot forward, turn left/right, or stop based on simple rule-based line-following logic.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-ir-line-sensors-line-follower-robot
// Parts used: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
//             https://shillehtek.com/products/n20-micro-metal-gear-motor-12v-100rpm
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#define IR_L A0
#define IR_R A1
#define IN1 8
#define IN2 9
#define IN3 10
#define IN4 11

// most TCRT5000 modules read LOW on the black line
#define ON_LINE LOW

void drive(bool l1, bool l2, bool r1, bool r2) {
  digitalWrite(IN1, l1); digitalWrite(IN2, l2);
  digitalWrite(IN3, r1); digitalWrite(IN4, r2);
}

void setup() {
  pinMode(IR_L, INPUT);  pinMode(IR_R, INPUT);
  pinMode(IN1, OUTPUT);  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);  pinMode(IN4, OUTPUT);
}

void loop() {
  bool leftOnLine  = (digitalRead(IR_L) == ON_LINE);
  bool rightOnLine = (digitalRead(IR_R) == ON_LINE);

  if (!leftOnLine && !rightOnLine)      drive(HIGH, LOW, HIGH, LOW);  // forward
  else if (leftOnLine && !rightOnLine)  drive(LOW,  LOW, HIGH, LOW);  // turn left
  else if (!leftOnLine && rightOnLine)  drive(HIGH, LOW, LOW,  LOW);  // turn right
  else                                  drive(LOW,  LOW, LOW,  LOW);  // stop
}
