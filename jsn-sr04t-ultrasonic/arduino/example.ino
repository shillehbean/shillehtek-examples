// Arduino sketch that triggers the JSN-SR04T, takes three readings (median), converts echo time to centimeters, and prints distance or status messages over Serial while handling blind-zone and out-of-range cases.
//
// Buy this module: https://shillehtek.com/products/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/jsn-sr04t-waterproof-ultrasonic-distance-sensor-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// JSN-SR04T Waterproof Ultrasonic - Arduino Example
// Trig->D9, Echo->D10, 5V, GND

const int trigPin = 9;
const int echoPin = 10;

long readOnceCm() {
  digitalWrite(trigPin, LOW);  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH); delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long us = pulseIn(echoPin, HIGH, 40000UL);   // 40 ms timeout
  return us == 0 ? -1 : us / 58;
}

long readMedianCm() {
  long a = readOnceCm(); delay(60);
  long b = readOnceCm(); delay(60);
  long c = readOnceCm();
  // median of three
  if ((a >= b) == (a <= c)) return a;
  if ((b >= a) == (b <= c)) return b;
  return c;
}

void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.println("JSN-SR04T ready (blind zone < ~25 cm)");
}

void loop() {
  long cm = readMedianCm();
  if (cm < 0)        Serial.println("Out of range / no echo");
  else if (cm < 25)  Serial.println("Too close (blind zone)");
  else {
    Serial.print("Distance: ");
    Serial.print(cm);
    Serial.println(" cm");
  }
  delay(300);
}
