// Sends a 150 ms HIGH pulse on digital pin D2 to trigger the relay (module set to "Delay-On"), repeating every 30 seconds.
//
// Buy this module: https://shillehtek.com/products/ac-220v-1-channel-time-delay-relay-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ac-220v-1-channel-time-delay-relay-module-manual
// More examples: https://github.com/shillehtek/examples
//

// 1-Channel programmable delay relay - fire trigger from Arduino
// Wire Trigger+ to D2, share GND. Module is set to "Delay-On" mode in its menu.

const int triggerPin = 2;

void setup() {
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
}

void loop() {
  digitalWrite(triggerPin, HIGH);
  delay(150);                     // 150 ms pulse fires the trigger
  digitalWrite(triggerPin, LOW);

  delay(30000);                   // wait 30 seconds before next trigger
}
