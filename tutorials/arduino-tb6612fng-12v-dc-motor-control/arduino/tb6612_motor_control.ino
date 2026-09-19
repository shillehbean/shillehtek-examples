// Demonstrates using the SparkFun_TB6612 library to drive a DC motor: full-speed forward and reverse, braking, and half-speed PWM with timed delays.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-tb6612fng-12v-dc-motor-control
// Parts used: https://shillehtek.com/products/tb6612fng-dual-motor-driver-module-arduino-esp32
//             https://shillehtek.com/products/n20-micro-metal-gear-motor-12v-100rpm
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SparkFun_TB6612.h>

// Pins - PWMA must be a PWM-capable pin
#define AIN1 5
#define AIN2 4
#define PWMA 10
#define STBY 9

const int offsetA = 1;               // flip to -1 to reverse "forward"
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

void setup() {
}

void loop() {
  motor1.drive(255, 1000);           // full speed forward, 1 s
  motor1.drive(-255, 1000);          // full speed reverse, 1 s
  motor1.brake();
  delay(1000);

  motor1.drive(128, 1000);           // half speed
  motor1.brake();
  delay(1000);
}
