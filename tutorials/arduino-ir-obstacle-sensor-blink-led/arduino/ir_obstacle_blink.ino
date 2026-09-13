// Reads a digital IR obstacle sensor, turns the built-in LED on when an obstacle is detected (active LOW), and sends a serial message.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-ir-obstacle-sensor-blink-led
// Parts used: https://shillehtek.com/products/ir-infrared-obstacle-avoidance-sensor-module-for-arduino-robot
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

const int IR  = 2;
const int LED = LED_BUILTIN;

void setup() {
  pinMode(IR, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(IR) == LOW) {   // active LOW = obstacle detected
    digitalWrite(LED, HIGH);
    Serial.println("Object detected!");
  } else {
    digitalWrite(LED, LOW);
  }
  delay(50);
}
