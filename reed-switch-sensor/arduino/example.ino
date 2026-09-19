// Reads a normally open reed switch on digital pin 2 with the internal pull-up, debounces contact bounce, and prints OPEN/CLOSED events to the Serial console.
//
// Buy this module: https://shillehtek.com/products/reed-switch-magnetic-sensor-normally-open-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/reed-switch-magnetic-sensor-normally-open-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Reed Switch Door Monitor - Arduino Example
// Lead 1 -> D2, Lead 2 -> GND (either way around)

const int reedPin = 2;
int lastState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(reedPin, INPUT_PULLUP);   // HIGH = open, LOW = magnet present
  Serial.println("Monitoring door...");
}

void loop() {
  int state = digitalRead(reedPin);

  if (state != lastState) {
    delay(30);                      // debounce contact bounce
    state = digitalRead(reedPin);
    if (state != lastState) {
      if (state == LOW) {
        Serial.println("CLOSED - magnet present");
      } else {
        Serial.println("OPEN - magnet away!");
        // trigger your alarm/notification here
      }
      lastState = state;
    }
  }
  delay(10);
}
