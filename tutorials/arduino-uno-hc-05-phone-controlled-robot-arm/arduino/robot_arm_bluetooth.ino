// Arduino sketch that controls six servos from an HC-05 Bluetooth connection, parsing commands like 's1NNN' to set servo angles and providing placeholders for speed control, save (record) and run (replay) motion steps.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-hc-05-phone-controlled-robot-arm
// Parts used: https://shillehtek.com/products/mg995-metal-gear-servo-motor-12kg-high-torque-180-degree-diy
//             https://shillehtek.com/products/hc-05-6pin-bluetooth-module-no-button
//             https://shillehtek.com/products/arduino-uno-r3-starter-kit
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <SoftwareSerial.h>
#include <Servo.h>

Servo servo01, servo02, servo03, servo04, servo05, servo06;
SoftwareSerial Bluetooth(3, 4);   // HC-05 TX -> D3, RX -> D4 (via divider)

int servo1Pos = 90, servo2Pos = 150, servo3Pos = 35,
    servo4Pos = 140, servo5Pos = 85, servo6Pos = 80;
String dataIn = "";

void setup() {
  servo01.attach(5);   // waist
  servo02.attach(6);   // shoulder
  servo03.attach(7);   // elbow
  servo04.attach(8);   // wrist roll
  servo05.attach(9);   // wrist pitch
  servo06.attach(10);  // gripper
  Bluetooth.begin(38400);
  Bluetooth.setTimeout(1);
  delay(20);
}

void loop() {
  if (Bluetooth.available() > 0) {
    dataIn = Bluetooth.readString();       // e.g. "s1120" = waist to 120 deg
    if (dataIn.startsWith("s1")) {
      servo1Pos = dataIn.substring(2).toInt();
      servo01.write(servo1Pos);
    }
    // ...same pattern for s2..s6, plus speed,
    // SAVE (record step) and RUN (replay saved steps)
  }
}
