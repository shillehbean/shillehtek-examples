// Arduino sketch for the Digispark ATtiny85 that reads a 10K NTC thermistor on A1 (physical P2), calculates temperature in Celsius using the B-coefficient (Steinhart formula), and sends readings over USB CDC when the host polls.
//
// Full tutorial: https://shillehtek.com/blogs/news/digispark-attiny85-thermistor-phone-thermometer-readout
// Parts used: https://shillehtek.com/products/attiny85-digispark-usb-arduino-development-board
//             https://shillehtek.com/products/10k-ntc-thermistor-temperature-sensor-mf52-103
//             https://shillehtek.com/products/820pcs-1-4w-1-41-kinds-each-value-20pcs-metal-film-resistors-kit-plastic-box
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <DigiCDC.h>

#define SERIESRESISTOR 10000
#define THERMISTORPIN A1        // physical pin P2
#define THERMISTORNOMINAL 10000 // 10K at 25 C
#define TEMPERATURENOMINAL 25
#define NUMSAMPLES 5
#define BCOEFFICIENT 3950

void setup() {
  SerialUSB.begin();
}

void loop()
{
  if (SerialUSB.available())
  {
    uint8_t i;
    float average;
    average = analogRead(THERMISTORPIN);

    average = 1023 / average - 1;
    average = SERIESRESISTOR / average;

    float steinhart;
    float presteinhart;
    steinhart = average / THERMISTORNOMINAL;     // R/Ro
    steinhart = log(steinhart);                  // ln(R/Ro)
    steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + 1/To
    steinhart = 1.0 / steinhart;                 // invert -> Kelvin
    steinhart -= 273.15;                         // to Celsius

    if (int(presteinhart) != int(steinhart))
    {
      SerialUSB.print("Temperature ");
      SerialUSB.print(steinhart);
      SerialUSB.println(" *C");
      presteinhart = steinhart;
    }
    SerialUSB.delay(1000);
  }
}
