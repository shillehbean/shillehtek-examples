// Runs a DC motor forward and reverse at specified PWM duty cycles and stops using an L298N motor driver.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-l298n-motor-driver-control-dc-motor-speed
// Parts used: https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int ENA = 9;
const int IN1 = 8;
const int IN2 = 7;

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  // Forward at 60% speed
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 153);
  delay(2000);

  // Reverse at 80% speed
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 204);
  delay(2000);

  // Stop
  analogWrite(ENA, 0);
  delay(1000);
}
