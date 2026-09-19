// Reads the KY-037 analog level from A0 and the digital trigger on D2, prints values over serial, and lights the onboard LED when sound is detected.
//
// Buy this module: https://shillehtek.com/products/shillehtek-ky-037-sound-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ky-037-sound-sensor-module-with-analog
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// KY-037 Sound Sensor - read analog level and digital trigger

const int analogPin = A0;
const int digitalPin = 2;
const int ledPin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(digitalPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int level = analogRead(analogPin);
  int trig  = digitalRead(digitalPin);

  Serial.print("Level: ");
  Serial.print(level);
  Serial.print("\tTrigger: ");
  Serial.println(trig == LOW ? "SOUND!" : "quiet");

  digitalWrite(ledPin, trig == LOW ? HIGH : LOW);
  delay(50);
}
