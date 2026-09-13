// Reads the WCS1700 current sensor using the Robojax_WCS library, prints measured current to Serial, and shows an example threshold-trigger action.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-wcs1700-measure-current-70a
// Parts used: https://shillehtek.com/products/wcs1700-70a-hall-current-sensor-module-overcurrent-detect
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Robojax_WCS.h>

// WCS1700 is model index 11 in the Robojax library
#define MODEL 11
#define SENSOR_PIN A0
#define SENSOR_VCC_PIN 8
#define ZERO_CURRENT_LED_PIN 2
#define ZERO_CURRENT_WAIT_TIME 5000
#define CORRECTION_VLALUE 164
#define MEASUREMENT_ITERATION 100
#define VOLTAGE_REFERENCE 5000.0
#define BIT_RESOLUTION 10
#define DEBUT_ONCE true

Robojax_WCS sensor(
  MODEL,
  SENSOR_PIN,
  SENSOR_VCC_PIN,
  ZERO_CURRENT_WAIT_TIME,
  ZERO_CURRENT_LED_PIN,
  CORRECTION_VLALUE,
  MEASUREMENT_ITERATION,
  VOLTAGE_REFERENCE,
  BIT_RESOLUTION,
  DEBUT_ONCE
);

void setup() {
  Serial.begin(9600);
  Serial.println("Robojax WCS Library");
  sensor.start();
  Serial.print("Sensor: ");
  Serial.println(sensor.getModel());
}

void loop() {
  sensor.readCurrent();
  sensor.printCurrent();

  // Example: trigger an action when current exceeds 12.3 A
  if (sensor.getCurrent() >= 12.3) {
    // Add your logic here (relay, alarm, logging, etc.)
  }

  delay(500);
  // Uncomment to see detailed debug info:
  // sensor.printDebug();
}
