// RF receiver sketch using the VirtualWire library to receive messages and display the received text on a 16x2 LiquidCrystal LCD.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-433mhz-rf-send-text-lcd
// Parts used: https://shillehtek.com/products/433mhz-rf-wireless-transmitter-receiver-link-kit-for-arduino
//             https://shillehtek.com/products/shillehtek-lcd1602-16x2-character-display-module
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

#include <VirtualWire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
char cad[100];
int pos = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(1, 0);
  vw_setup(2000);
  vw_rx_start();
}

void loop()
{
  byte buf[VW_MAX_MESSAGE_LEN];
  byte buflen = VW_MAX_MESSAGE_LEN;
  int i;

  if (vw_get_message(buf, &buflen))
  {
    if (pos < 2)
      lcd.setCursor(0, pos);
    else
    {
      pos = 0;
      lcd.clear();
    }

    for (i = 1; i < buflen; i++)
    {
      lcd.print((char)buf[i]);
      pos++;
    }
  }
}
