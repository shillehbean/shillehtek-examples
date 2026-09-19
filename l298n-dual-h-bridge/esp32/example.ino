// ESP32 sketch using LEDC PWM to control two DC motors through the L298N, demonstrating forward, reverse, and stop sequences.
//
// Buy this module: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/l298n-motor-driver-controller-board-module-for-stepper-motor-dc-dual-h-bridge
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// L298N on ESP32 - dual DC motors using LEDC PWM

const int ENA = 13, IN1 = 14, IN2 = 27;
const int ENB = 33, IN3 = 26, IN4 = 25;
const int PWM_FREQ = 20000, PWM_RES = 8;

void setup() {
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);

  ledcAttach(ENA, PWM_FREQ, PWM_RES);
  ledcAttach(ENB, PWM_FREQ, PWM_RES);
}

void motor(int enPin, int in1, int in2, int speed) {
  digitalWrite(in1, speed > 0);
  digitalWrite(in2, speed < 0);
  ledcWrite(enPin, abs(speed));
}

void loop() {
  motor(ENA, IN1, IN2, 200); motor(ENB, IN3, IN4, 200); delay(2000);
  motor(ENA, IN1, IN2, -200); motor(ENB, IN3, IN4, -200); delay(2000);
  motor(ENA, IN1, IN2, 0);  motor(ENB, IN3, IN4, 0);  delay(1000);
}
