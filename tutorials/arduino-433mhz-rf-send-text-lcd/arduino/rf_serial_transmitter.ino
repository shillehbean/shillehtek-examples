// RF transmitter sketch that reads characters from Serial until a '.' terminator and sends the collected string via VirtualWire.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-433mhz-rf-send-text-lcd
// Parts used: https://shillehtek.com/products/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <VirtualWire.h>

char cad[100];
int i = 0;

void setup()
{
  Serial.begin(9600);
  vw_setup(2000);
  Serial.print("End with \".\" each data");
}

void loop()
{
  if (Serial.available() > 0)
  {
    cad[i] = Serial.read();
    i++;
  }

  if (cad[i - 1] == '.')
  {
    cad[i] = '\0';
    i = 0;
    vw_send((byte *)cad, strlen(cad));
    delay(400);
  }
}
