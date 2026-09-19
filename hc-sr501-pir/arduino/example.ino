// Basic Arduino sketch that reads the PIR on digital pin 2, turns the onboard LED on when motion is detected, and prints status messages over Serial (includes a 30s warm-up).
//
// Buy this module: https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr501-pir-motion-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// HC-SR501 PIR Motion Sensor - basic motion detection

const int pirPin = 2;
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("PIR warming up... wait 30-60 seconds.");
  delay(30000);
  Serial.println("Ready.");
}

void loop() {
  int state = digitalRead(pirPin);
  if (state == HIGH) {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion detected!");
  } else {
    digitalWrite(ledPin, LOW);
  }
  delay(100);
}
