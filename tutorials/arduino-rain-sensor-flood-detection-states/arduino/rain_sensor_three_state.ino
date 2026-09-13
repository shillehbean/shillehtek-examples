// Reads the rain sensor on analog pin A0, maps the reading into three zones, and prints Flood / Rain Warning / Not Raining to the serial console.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-rain-sensor-flood-detection-states
// Parts used: https://shillehtek.com/products/sensor-rain-water-level-arduino-raspberry-pi-esp32
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// Rain sensor three-state example (after Reichenstein7)
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

void setup() {
  Serial.begin(9600);
}

void loop() {
  // read the sensor on analog A0:
  int sensorReading = analogRead(A0);
  // map the range to three zones:
  int range = map(sensorReading, sensorMin, sensorMax, 0, 3);

  switch (range) {
    case 0:    // board is soaked
      Serial.println("Flood");
      break;
    case 1:    // droplets on the board
      Serial.println("Rain Warning");
      break;
    case 2:    // board is dry
      Serial.println("Not Raining");
      break;
  }
  delay(1);
}
