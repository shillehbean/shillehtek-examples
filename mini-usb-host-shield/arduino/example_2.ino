// Sets up the USB host as a HID keyboard reader and echoes characters from a connected USB keyboard to the Serial console.
//
// Buy this module: https://shillehtek.com/products/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/mini-usb-host-shield-2-0-adk-module-max3421e-for-arduino-pro-mini-manual
// More examples: https://github.com/shillehtek/examples
//

#include <hidboot.h>
#include <usbhub.h>

class KbdRptParser : public KeyboardReportParser {
  void OnKeyDown(uint8_t mod, uint8_t key) override {
    uint8_t c = OemToAscii(mod, key);
    if (c) Serial.write(c);
  }
};

USB              Usb;
USBHub           Hub(&Usb);
HIDBoot<USB_HID_PROTOCOL_KEYBOARD> Keyboard(&Usb);
KbdRptParser     Prs;

void setup() {
  Serial.begin(115200);
  if (Usb.Init() == -1) { Serial.println("Init failed"); while (1); }
  delay(200);
  Keyboard.SetReportParser(0, &Prs);
}

void loop() {
  Usb.Task();
}
