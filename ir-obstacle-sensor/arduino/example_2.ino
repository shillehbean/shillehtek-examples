// Uses the sensor on D2 to stop or run two motors by PWM-ing motor enable pins (9 and 10), halting the robot when an obstacle is detected.
//
// Buy this module: https://shillehtek.com/products/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot-manual
// More examples: https://github.com/shillehtek/examples
//

// Front-mounted IR obstacle sensor stops the robot when something is close
// OUT to D2; motor enable pins go to your motor driver

const int sensorPin = 2;
const int motorL = 9;
const int motorR = 10;
const int speed = 180;

void setup() {
  pinMode(sensorPin, INPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
}

void loop() {
  if (digitalRead(sensorPin) == LOW) {
    analogWrite(motorL, 0);
    analogWrite(motorR, 0);
    delay(500);                  // pause
  } else {
    analogWrite(motorL, speed);
    analogWrite(motorR, speed);
  }
}
