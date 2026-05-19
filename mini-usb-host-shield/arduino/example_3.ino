// Uses the PS4USB driver to read input from a wired PS4 controller over USB and prints analog stick positions and a button press state to Serial when connected.
//
// Buy this module: https://shillehtek.com/products/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini-manual
// More examples: https://github.com/shillehtek/examples
//

// Bluetooth via the same library, or wired USB.
// This sketch shows wired PS4 over USB.

#include <PS4USB.h>

USB     Usb;
PS4USB  PS4(&Usb);

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) { Serial.println("Init failed"); while (1); }
}

void loop() {
  Usb.Task();
  if (PS4.connected()) {
    Serial.print("LX="); Serial.print(PS4.getAnalogHat(LeftHatX));
    Serial.print(" LY="); Serial.print(PS4.getAnalogHat(LeftHatY));
    Serial.print(" X="); Serial.println(PS4.getButtonClick(CROSS));
  }
}
