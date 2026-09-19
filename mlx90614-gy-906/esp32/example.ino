// Initializes I2C on an ESP32 (GPIO21 SDA, GPIO22 SCL), reads ambient and object temperatures from the MLX90614, and prints them to Serial at 115200 baud.
//
// Buy this module: https://shillehtek.com/products/pre-soldered-gy-906-mlx90614-baa-infrared-temperature-sensor
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/gy-906-mlx90614-baa-non-touch-infrared-temperature-sensor
// More examples: https://github.com/shillehbean/shillehtek-examples
//

// MLX90614 on ESP32 via I2C (GPIO21 SDA, GPIO22 SCL)

#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  if (!mlx.begin()) {
    Serial.println("MLX90614 not found.");
    while (1);
  }
  Serial.println("MLX90614 ready.");
}

void loop() {
  Serial.printf("Ambient: %.2f C | Object: %.2f C\n",
                mlx.readAmbientTempC(),
                mlx.readObjectTempC());
  delay(500);
}
