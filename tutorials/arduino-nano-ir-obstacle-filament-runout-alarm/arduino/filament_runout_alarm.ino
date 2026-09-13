// Reads an IR obstacle sensor on digital pin 2 and sounds a piezo buzzer on pin 8 with a repeating tone pattern when filament is absent.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-nano-ir-obstacle-filament-runout-alarm
// Parts used: https://shillehtek.com/products/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot
//             https://shillehtek.com/products/ky-006-passive-piezo-buzzer-alarm-module-for-arduino-projects
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int IR = 2;
const int BUZZ = 8;
void setup() {
  pinMode(IR, INPUT);
  pinMode(BUZZ, OUTPUT);
  Serial.begin(9600);
}
void loop() {
  if (digitalRead(IR) == HIGH) {   // filament absent
    Serial.println("FILAMENT OUT");
    for (int i = 0; i < 5; i++) {
      tone(BUZZ, 1500, 300); delay(400);
    }
  }
  delay(50);
}
