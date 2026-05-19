// Implements a simple 3-sensor line-following routine that reads three digital TCRT5000 outputs and sets two PWM motor outputs to drive straight, turn left/right, or stop.
//
// Buy this module: https://shillehtek.com/products/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot-manual
// More examples: https://github.com/shillehtek/examples
//

// 3-sensor line follower using three TCRT5000 modules
// Sensors face the floor across the robot's width
// Left = D2, Center = D3, Right = D4
// Motor pins go to your motor driver of choice

const int sLeft = 2, sCenter = 3, sRight = 4;
const int motorL = 9, motorR = 10;   // PWM motor speeds

void setup() {
  pinMode(sLeft, INPUT);
  pinMode(sCenter, INPUT);
  pinMode(sRight, INPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
}

void loop() {
  bool L = digitalRead(sLeft)   == LOW;   // LOW = on line
  bool C = digitalRead(sCenter) == LOW;
  bool R = digitalRead(sRight)  == LOW;

  if (C && !L && !R)        { analogWrite(motorL, 180); analogWrite(motorR, 180); } // straight
  else if (L && !R)          { analogWrite(motorL, 80);  analogWrite(motorR, 200); } // turn left
  else if (R && !L)          { analogWrite(motorL, 200); analogWrite(motorR, 80);  } // turn right
  else                       { analogWrite(motorL, 0);   analogWrite(motorR, 0);   } // stop
}
