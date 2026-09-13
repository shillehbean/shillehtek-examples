// Reads analog voltage from the anemometer on A0, converts it to wind speed using calibrated min/max voltages, and prints voltage and wind speed to the Serial Monitor every second.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-anemometer-measure-wind-speed
// Parts used: https://shillehtek.com/products/anemometer-wind-speed-0-5v-analog-output
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

int sensorPin = A0;
int sensorValue = 0;
float sensorVoltage = 0;
float windSpeed = 0;

float voltageConversionConstant = .004882814; // 5V / 1024 steps
int sensorDelay = 1000;

float voltageMin = .4;      // sensor voltage at zero wind
float windSpeedMin = 0;
float voltageMax = 2.0;     // sensor voltage at max rated wind
float windSpeedMax = 32;    // max rated wind speed

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(sensorPin);
  sensorVoltage = sensorValue * voltageConversionConstant;

  if (sensorVoltage <= voltageMin) {
    windSpeed = 0;
  } else {
    windSpeed = (sensorVoltage - voltageMin) * windSpeedMax / (voltageMax - voltageMin);
  }

  Serial.print("Voltage: ");
  Serial.print(sensorVoltage);
  Serial.print("\t");
  Serial.print("Wind speed: ");
  Serial.println(windSpeed);
  delay(sensorDelay);
}
