// Controls the pump via a MOSFET/transistor on digital pin D9, turning the pump on for 3 seconds and off for 27 seconds in a repeating 30-second cycle while printing state to Serial.
//
// Buy this module: https://shillehtek.com/products/mini-submersible-water-pump-3-5v-arduino-raspberry
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-submersible-water-pump-3-5v-arduino-raspberry-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Mini pump on a MOSFET/transistor, control pin D9.
// Runs the pump 3 s every 30 s - adjust for your plant.

const int PUMP_PIN = 9;

void setup() {
  pinMode(PUMP_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.println("Pump ON");
  digitalWrite(PUMP_PIN, HIGH);
  delay(3000);                    // pump for 3 seconds

  Serial.println("Pump OFF");
  digitalWrite(PUMP_PIN, LOW);
  delay(27000);                   // wait 27 seconds
}
