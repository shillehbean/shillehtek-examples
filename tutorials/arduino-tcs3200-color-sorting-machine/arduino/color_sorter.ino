// Reads RGB frequency values from a TCS3200 sensor and moves a servo to route detected colors into different bins.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-tcs3200-color-sorting-machine
// Parts used: https://shillehtek.com/products/gy-31-tcs3200-rgb-color-recognition-sensor-for-arduino-projects
//             https://shillehtek.com/products/mg90s-metal-gear-micro-servo-motor-180-degree-9g-for-rc-plane
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Servo.h>
const int S0=4,S1=5,S2=6,S3=7,OUT=8;
Servo arm;
int readCh(bool s2,bool s3){ digitalWrite(S2,s2);digitalWrite(S3,s3);delay(50);return pulseIn(OUT,LOW); }
void setup() {
  for (int p:{S0,S1,S2,S3}) pinMode(p,OUTPUT);
  pinMode(OUT,INPUT);
  digitalWrite(S0,HIGH); digitalWrite(S1,HIGH);
  arm.attach(9); arm.write(90);
}
void loop() {
  int r=readCh(LOW,LOW), g=readCh(HIGH,HIGH), b=readCh(LOW,HIGH);
  if (r < g && r < b)        arm.write(0);    // red bin
  else if (g < r && g < b)   arm.write(60);   // green bin
  else if (b < r && b < g)   arm.write(120);  // blue bin
  else                          arm.write(180);  // yellow / unknown
  delay(800);
  arm.write(90);
  delay(2000);
}
