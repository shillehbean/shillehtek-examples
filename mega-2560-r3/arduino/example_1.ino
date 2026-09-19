// Blinks the onboard LED on pin 13 and writes LED state messages to the USB Serial Monitor at 9600 baud.
//
// Buy this module: https://shillehtek.com/products/mega-2560-r3-ch340-arduino-board
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mega-2560-r3-ch340-arduino-board-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MEGA 2560 R3 - Blink the onboard LED and print to Serial Monitor
// No wiring required: the LED is built in on pin 13

const int LED_PIN = 13;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);          // open USB serial
  Serial.println("MEGA 2560 R3 is alive!");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED ON");
  delay(500);
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED OFF");
  delay(500);
}
