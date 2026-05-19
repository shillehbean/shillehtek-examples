// Reads the HC-SR04 using Arduino pins 9 (Trig) and 10 (Echo), calculates distance in centimeters, and prints it to Serial every 500 ms.
//
// Buy this module: https://shillehtek.com/products/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/hc-sr04-ultrasonic-distance-sensor-module-4-pin-for-arduino-manual
// More examples: https://github.com/shillehtek/examples
//

// HC-SR04 Ultrasonic Distance Sensor - Arduino Example
// Trig Pin: 9, Echo Pin: 10

const int trigPin = 9;
const int echoPin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Send a 10 microsecond pulse to trigger the sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the echo pulse
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in cm (sound travels 34300 cm/s)
  // distance = duration / 2 / 29.1
  float distance = duration * 0.034 / 2;

  // Print the distance
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(500);
}
