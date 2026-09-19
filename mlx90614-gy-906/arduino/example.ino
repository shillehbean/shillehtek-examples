// Reads ambient and object temperatures from an MLX90614 using the Adafruit_MLX90614 library and prints the values to the Serial console every 500 ms.
//
// Buy this module: https://shillehtek.com/products/pre-soldered-gy-906-mlx90614-baa-infrared-temperature-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-906-mlx90614-baa-non-touch-infrared-temperature-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MLX90614 - Read ambient and object temperature
// Requires: Adafruit MLX90614 Library

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  }
  Serial.println("MLX90614 ready.");
}

void loop() {
  Serial.print("Ambient = ");
  Serial.print(mlx.readAmbientTempC());
  Serial.print(" C\tObject = ");
  Serial.print(mlx.readObjectTempC());
  Serial.println(" C");
  delay(500);
}
