// Reads analog reflectance values from a TCRT5000 sensor connected to A0 and prints them to the Serial Monitor.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-uno-tcrt5000-analog-line-sensor-readings
// Parts used: https://shillehtek.com/products/tcrt5000-ir-reflective-line-follower-sensor-for-arduino-robot
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// TCRT5000 IR Sensor Analog Read
// Reads reflected IR intensity from the TCRT5000 module

void setup() {
  // Start serial communication at 9600 baud
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from pin A0
  int sensorValue = analogRead(A0);

  // Print the sensor reading to the serial monitor
  Serial.println(sensorValue);

  // Short delay between readings
  delay(100);
}
