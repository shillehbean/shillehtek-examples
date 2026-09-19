// Arduino sketch controlling two DC motors via the L298N using PWM on EN pins and digital IN pins to run forward, reverse, and stop.
//
// Buy this module: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/l298n-motor-driver-controller-board-module-for-stepper-motor-dc-dual-h-bridge
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// L298N - Drive 2 DC motors forward, backward, and stop
// Motor A: ENA=D9, IN1=D8, IN2=D7
// Motor B: ENB=D3, IN3=D5, IN4=D4

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;
const int ENB = 3;
const int IN3 = 5;
const int IN4 = 4;

void setup() {
  pinMode(ENA, OUTPUT); pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT); pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
}

void setMotor(int enPin, int in1, int in2, int speed) {
  // speed: -255 (full back) .. 255 (full fwd). 0 = stop.
  digitalWrite(in1, speed > 0 ? HIGH : LOW);
  digitalWrite(in2, speed < 0 ? HIGH : LOW);
  analogWrite(enPin, abs(speed));
}

void loop() {
  setMotor(ENA, IN1, IN2, 200);   // Motor A forward ~80%
  setMotor(ENB, IN3, IN4, 200);   // Motor B forward ~80%
  delay(2000);

  setMotor(ENA, IN1, IN2, -150);  // Motor A reverse ~60%
  setMotor(ENB, IN3, IN4, -150);
  delay(2000);

  setMotor(ENA, IN1, IN2, 0);     // stop
  setMotor(ENB, IN3, IN4, 0);
  delay(1000);
}
