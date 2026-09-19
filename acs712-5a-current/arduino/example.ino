// Reads the ACS712 output on Arduino A0, calibrates the zero offset at startup, and prints measured voltage and calculated DC current over Serial.
//
// Buy this module: https://shillehtek.com/products/acs712-current-sensor-5a-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/acs712-current-sensor-5a-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// ACS712 5A Current Sensor - Arduino Example (DC current)
// OUT -> A0, VCC -> 5V, GND -> GND, load in series through IP+/IP-

const int sensorPin = A0;
const float SENSITIVITY = 0.185;   // volts per amp (5A version)
float zeroVolts = 2.5;             // measured at startup

float readVolts(int samples) {
  long total = 0;
  for (int i = 0; i < samples; i++) {
    total += analogRead(sensorPin);
    delay(1);
  }
  return (total / (float)samples) * (5.0 / 1023.0);
}

void setup() {
  Serial.begin(9600);

  // Calibrate the zero point - no load current for these 2 seconds!
  Serial.println("Calibrating zero point, keep load OFF...");
  zeroVolts = readVolts(500);
  Serial.print("Zero = ");
  Serial.print(zeroVolts, 3);
  Serial.println(" V. Measuring...");
}

void loop() {
  float volts = readVolts(100);
  float amps = (volts - zeroVolts) / SENSITIVITY;

  Serial.print("OUT: ");
  Serial.print(volts, 3);
  Serial.print(" V | Current: ");
  Serial.print(amps, 3);
  Serial.println(" A");

  delay(500);
}
