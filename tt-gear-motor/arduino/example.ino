// Controls a TT gear motor from an Arduino using an L298N (IN1/IN2 for direction, ENA for PWM), cycling forward, stop, and reverse.
//
// Buy this module: https://shillehtek.com/products/tt-gear-motor-3-6v-1-48-125rpm
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tt-gear-motor-3-6v-1-48-125rpm-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// One TT motor on L298N: IN1=D8, IN2=D7, ENA=D9 (PWM)

const int IN1 = 8;
const int IN2 = 7;
const int ENA = 9;

void setMotor(int speed) {
  // speed: -255 (full reverse) .. 255 (full forward)
  if (speed >= 0) {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    speed = -speed;
  }
  analogWrite(ENA, speed);
}

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  setMotor(180);    // forward, ~70%
  delay(2000);
  setMotor(0);      // stop
  delay(500);
  setMotor(-180);   // reverse
  delay(2000);
  setMotor(0);
  delay(500);
}
