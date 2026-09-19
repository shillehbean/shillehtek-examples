// Samples the sensor on A0, calibrates a zero-voltage baseline, converts the measured voltage to gauss, and prints field strength and pole to the serial monitor.
//
// Buy this module: https://shillehtek.com/products/linear-hall-effect-sensor-49e-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/linear-hall-effect-sensor-49e-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// 49E Linear Hall Effect Sensor - Arduino Example
// OUT -> A0, VCC -> 5V, GND -> GND

const int hallPin = A0;
const float MV_PER_GAUSS = 1.4;   // ~1.4 mV/G at 5V supply
float zeroVolts = 2.5;

float readVolts(int samples) {
  long total = 0;
  for (int i = 0; i < samples; i++) {
    total += analogRead(hallPin);
    delay(2);
  }
  return (total / (float)samples) * (5.0 / 1023.0);
}

void setup() {
  Serial.begin(9600);
  Serial.println("Calibrating - keep magnets away...");
  delay(1000);
  zeroVolts = readVolts(200);
  Serial.print("Zero point: ");
  Serial.print(zeroVolts, 3);
  Serial.println(" V. Bring a magnet close!");
}

void loop() {
  float volts = readVolts(20);
  float gauss = (volts - zeroVolts) * 1000.0 / MV_PER_GAUSS;

  Serial.print("OUT: ");
  Serial.print(volts, 3);
  Serial.print(" V | ~");
  Serial.print(gauss, 0);
  Serial.print(" G ");

  if (gauss > 15)       Serial.println("(south pole)");
  else if (gauss < -15) Serial.println("(north pole)");
  else                  Serial.println("(no field)");

  delay(300);
}
