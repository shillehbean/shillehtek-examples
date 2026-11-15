// Reads the MAX9814 analog output over a 50 ms window, computes peak-to-peak sound level, and prints the value over Serial (works for AVR and ESP32 builds).
//
// Buy this module: https://shillehtek.com/products/max9814-microphone-agc-amplifier-module-pre-soldered-header
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/max9814-microphone-agc-amplifier-module-pre-soldered-header-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MAX9814 microphone amplifier - print the sound level (peak-to-peak)
// Arduino Uno/Nano: Vdd = 3.3V, GND = GND, Out = A0
// ESP32:            Vdd = 3V3,  GND = GND, Out = GPIO 34
#if defined(ESP32)
const int MIC_PIN = 34;
const int ADC_MAX = 4095;             // 12-bit ADC
#else
const int MIC_PIN = A0;
const int ADC_MAX = 1023;             // 10-bit ADC
#endif

const unsigned long WINDOW_MS = 50;   // listen for 50 ms per reading

void setup() {
  Serial.begin(115200);
}

void loop() {
  int lowest = ADC_MAX;
  int highest = 0;
  unsigned long start = millis();
  while (millis() - start < WINDOW_MS) {
    int value = analogRead(MIC_PIN);
    if (value < lowest) lowest = value;
    if (value > highest) highest = value;
  }
  Serial.print("Sound level: ");
  Serial.println(highest - lowest);
}
