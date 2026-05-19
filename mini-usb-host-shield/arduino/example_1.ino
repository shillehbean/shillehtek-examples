// Initializes the MAX3421E-based USB host, reports initialization status over Serial, and runs the USB task loop while prompting to plug in a device.
//
// Buy this module: https://shillehtek.com/products/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini-manual
// More examples: https://github.com/shillehtek/examples
//

// Install "USB Host Shield Library 2.0" by felis
// File > Examples > USB Host Shield Library 2.0 > USB_desc

#include <usbhub.h>

USB     Usb;
USBHub  Hub(&Usb);

void setup() {
  Serial.begin(115200);
  while (!Serial);
  if (Usb.Init() == -1) {
    Serial.println("MAX3421E NOT FOUND - check wiring");
    while (1);
  }
  Serial.println("USB Host ready. Plug in a device...");
}

void loop() {
  Usb.Task();
}
