// Attach the SW-420 to an interrupt-capable Arduino pin, count vibration pulses in an ISR, and print a once-per-second vibration intensity summary over Serial.
//
// Buy this module: https://shillehtek.com/products/vibration-sensor-sw-420-arduino-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/vibration-sensor-sw-420-arduino-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// SW-420 Vibration Sensor - Arduino Example (interrupt pulse counting)
// DO -> Pin 2, VCC -> 5V, GND -> GND

const int sensorPin = 2;               // interrupt-capable pin
volatile unsigned int pulseCount = 0;

void onVibration() {
  pulseCount++;                        // keep the ISR tiny
}

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);
  // CHANGE catches every edge, so idle-HIGH boards work too
  attachInterrupt(digitalPinToInterrupt(sensorPin), onVibration, CHANGE);
  Serial.println("Monitoring vibration...");
}

void loop() {
  // Report once per second
  noInterrupts();
  unsigned int count = pulseCount;
  pulseCount = 0;
  interrupts();

  if (count == 0) {
    Serial.println("Still");
  } else if (count < 20) {
    Serial.print("Light vibration  (");
    Serial.print(count);
    Serial.println(" pulses)");
  } else {
    Serial.print("STRONG vibration (");
    Serial.print(count);
    Serial.println(" pulses)");
  }

  delay(1000);
}
