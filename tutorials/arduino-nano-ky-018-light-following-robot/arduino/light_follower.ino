// Full Arduino sketch that reads two LDRs and sets motor directions and PWM speeds to steer the robot toward the brighter light.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ky-018-light-following-robot
// Parts used: https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/photoresistor-light-sensor-ky-018-arduino-esp32
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int LEFT_LDR  = A0;
const int RIGHT_LDR = A1;
const int LEFT_PWM  = 3;
const int RIGHT_PWM = 11;
const int L_A = 5, L_B = 6;
const int R_A = 9, R_B = 10;
const int BASE_SPEED = 150;

void setMotor(int a, int b, int pwm, int speed) {
  digitalWrite(a, speed > 0 ? HIGH : LOW);
  digitalWrite(b, speed > 0 ? LOW : HIGH);
  analogWrite(pwm, abs(speed));
}

void setup() {
  pinMode(L_A, OUTPUT); pinMode(L_B, OUTPUT);
  pinMode(R_A, OUTPUT); pinMode(R_B, OUTPUT);
}

void loop() {
  int L = analogRead(LEFT_LDR);
  int R = analogRead(RIGHT_LDR);
  int diff = L - R;     // positive = light is on left side

  int leftSpeed  = BASE_SPEED - diff / 4;
  int rightSpeed = BASE_SPEED + diff / 4;
  leftSpeed  = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  setMotor(L_A, L_B, LEFT_PWM,  leftSpeed);
  setMotor(R_A, R_B, RIGHT_PWM, rightSpeed);

  delay(50);
}
