// Reads the analog moisture sensor on ADC pin 34, converts the 12-bit ADC value to a percentage, and prints the moisture percent to Serial every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/esp32-soil-moisture-sensor-wifi-dashboard-readout
// Parts used: https://shillehtek.com/products/esp32-wroom-dev-board-cp2102-usb-c-presoldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

int moisturePercent;
int sensorAnalog;

// Change this to the ADC pin you are using
const int sensorPin = 34;

void setup() {
  Serial.begin(115200);
}

void loop() {
  sensorAnalog = analogRead(sensorPin);
  moisturePercent = 100 - ((sensorAnalog / 4095.00) * 100);

  Serial.print("Moisture = ");
  Serial.print(moisturePercent);
  Serial.println("%");

  delay(1000);
}
