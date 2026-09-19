// Reads the GUVA-S12SD on Arduino A0, averages multiple 10-bit ADC samples, converts the result to millivolts assuming a 5V reference, estimates UV index as mV/100, and prints voltage and UV index over Serial.
//
// Buy this module: https://shillehtek.com/products/uv-sensor-guva-s12sd-arduino-esp32
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/uv-sensor-guva-s12sd-arduino-esp32-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// GUVA-S12SD UV Sensor - Arduino Example
// SIG Pin: A0, VCC: 5V, GND: GND
// UV Index is approximately the output voltage in mV divided by 100

const int sigPin = A0;
const int numSamples = 16;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Average several readings to smooth out ADC noise
  long total = 0;
  for (int i = 0; i < numSamples; i++) {
    total += analogRead(sigPin);
    delay(2);
  }
  float raw = total / (float)numSamples;

  // Convert the 10-bit reading (0-1023) to millivolts (5V reference)
  float millivolts = raw * (5000.0 / 1023.0);

  // Approximate solar UV Index: mV / 100
  float uvIndex = millivolts / 100.0;

  Serial.print("Voltage: ");
  Serial.print(millivolts, 0);
  Serial.print(" mV | UV Index: ");
  Serial.println(uvIndex, 1);

  delay(1000);
}
