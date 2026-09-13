// Initializes the MLX90614 sensor over I2C and prints ambient and object temperatures (in °C) to the serial console every 500 ms.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-mlx90614-non-contact-temperature-reading
// Parts used: https://shillehtek.com/products/pre-soldered-gy-906-mlx90614-baa-infrared-temperature-sensor
//             https://shillehtek.com/products/arduino-nano-v3-presoldered-ch340g-atmega328p
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  if (!mlx.begin()) { Serial.println("MLX not found"); while (1); }
}

void loop() {
  Serial.print("Ambient="); Serial.print(mlx.readAmbientTempC(), 1);
  Serial.print(" C  Object="); Serial.print(mlx.readObjectTempC(), 1);
  Serial.println(" C");
  delay(500);
}
