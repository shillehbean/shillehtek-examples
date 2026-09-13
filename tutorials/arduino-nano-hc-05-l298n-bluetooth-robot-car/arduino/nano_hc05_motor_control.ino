// Reads single-character commands from Serial (e.g., from an HC-05 Bluetooth module) and controls two DC motors via an L298N driver for forward, reverse, left, right, and stop.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-hc-05-l298n-bluetooth-robot-car
// Parts used: https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
//             https://shillehtek.com/products/shillehtek-l298n-motor-driver-controller-board
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int IN1=6,IN2=7,IN3=8,IN4=9,ENA=5,ENB=10;
void setup() { Serial.begin(9600);
  for (int p : {IN1,IN2,IN3,IN4,ENA,ENB}) pinMode(p,OUTPUT);
  analogWrite(ENA,200); analogWrite(ENB,200);
}
void stop(){ digitalWrite(IN1,LOW);digitalWrite(IN2,LOW);digitalWrite(IN3,LOW);digitalWrite(IN4,LOW); }
void fwd(){ digitalWrite(IN1,HIGH);digitalWrite(IN2,LOW);digitalWrite(IN3,HIGH);digitalWrite(IN4,LOW); }
void rev(){ digitalWrite(IN1,LOW);digitalWrite(IN2,HIGH);digitalWrite(IN3,LOW);digitalWrite(IN4,HIGH); }
void left(){ digitalWrite(IN1,LOW);digitalWrite(IN2,HIGH);digitalWrite(IN3,HIGH);digitalWrite(IN4,LOW); }
void right(){ digitalWrite(IN1,HIGH);digitalWrite(IN2,LOW);digitalWrite(IN3,LOW);digitalWrite(IN4,HIGH); }
void loop() {
  if (!Serial.available()) return;
  char c = Serial.read();
  if (c=='F') fwd(); else if (c=='B') rev();
  else if (c=='L') left(); else if (c=='R') right();
  else if (c=='S') stop();
}
