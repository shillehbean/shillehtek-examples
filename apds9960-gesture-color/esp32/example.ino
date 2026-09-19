// Initializes the APDS-9960 on an ESP32 using default I2C pins, enables proximity and ambient/RGB light sensors, and polls the sensor to read proximity and RGB/ambient values for serial output.
//
// Buy this module: https://shillehtek.com/products/apds-9960-gesture-proximity-color-sensor-module
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/apds-9960-gesture-proximity-color-sensor-module-manual
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// APDS-9960 Proximity + RGB Color - ESP32 Arduino Example
// SDA: GPIO 21, SCL: GPIO 22 (ESP32 default I2C pins), VCC: 3V3
// Library: "SparkFun APDS9960 RGB and Gesture Sensor" (Library Manager)

#include <Wire.h>
#include <SparkFun_APDS9960.h>

SparkFun_APDS9960 apds = SparkFun_APDS9960();

uint8_t proximity = 0;
uint16_t ambient = 0, red = 0, green = 0, blue = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);  // SDA = GPIO 21, SCL = GPIO 22

  if (apds.init()) {
    Serial.println("APDS-9960 initialized");
  } else {
    Serial.println("Init failed! Check wiring and 3V3 power.");
  }

  // Start the proximity engine (false = no interrupts, we poll instead)
  if (!apds.enableProximitySensor(false)) {
    Serial.println("Could not start proximity sensor");
  }

  // Start the ambient light / RGB color engine
  if (!apds.enableLightSensor(false)) {
    Serial.println("Could not start light sensor");
  }

  delay(500);  // Give the sensor time to settle
}

void loop() {
  apds.readProximity(proximity);      // 0 (nothing near) to 255 (very close)
  apds.readAmbientLight(ambient);     // 16-bit clear channel
  apds.readRedLight(red);
  apds.readGreenLight(green);
  apds.readBlueLight(blue);

  Serial.print("Proximity: ");
  Serial.print(proximity);
  Serial.print(" | Ambient: ");
  Serial.print(ambient);
  Serial.print(" | R: ");
  Serial.print(red);
  Serial.print(" G: ");
  Serial.print(green);
  Serial.print(" B: ");
  Serial.println(blue);

  delay(500);
}
