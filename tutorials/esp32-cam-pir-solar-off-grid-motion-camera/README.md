# ESP32-CAM PIR: Solar Off-Grid Motion Camera

This tutorial shows how to build a solar-powered, off-grid motion camera using an ESP32-CAM and a PIR sensor that wakes the board from deep sleep to capture and upload photos to Telegram. The code in this folder initializes the camera, connects to WiFi, takes a photo when triggered, posts it to Telegram, and configures the ESP32 deep-sleep wakeup via an RTC GPIO connected to the PIR.

**Read the full tutorial:** [ESP32-CAM PIR: Solar Off-Grid Motion Camera](https://shillehtek.com/blogs/news/esp32-cam-pir-solar-off-grid-motion-camera)  
**Parts used:** [110 x 136mm 6V 2W Solar Panel](https://shillehtek.com/products/110-x-136mm-6v-2w-solar-panel) · [CN3791 6V MPPT Solar Charger Module](https://shillehtek.com/products/cn3791-6v-mppt-solar-charger-module) · [1S 3.7V 3A 2MOS BMS Li-ion 18650 Battery Protection Board](https://shillehtek.com/products/1s-3-7v-3a-2mos-bms-li-ion-18650-battery-protection-board) · [18650 Battery Holder Box with Wire (No Cover)](https://shillehtek.com/products/1-x-18650-battery-holder-box-with-wire-no-cover) · [HC-SR501 PIR Motion Sensor for Arduino & Raspberry Pi](https://shillehtek.com/products/shillehtek-hc-sr501-pir-motion-sensor-module) · [HLK-2410C Human Presence Radar Motion Detection Module (Pre-Soldered)](https://shillehtek.com/products/hlk-2410c-human-presence-radar-motion-detection-module-pre-soldered) · [ESP32-CAM Development Board with OV3660 Camera, WiFi + Bluetooth, Pre-Soldered with Foam](https://shillehtek.com/products/kuongshun-esp32-cam-development-board-wifi-bluetooth-module-with-ov3660-camera-with-soldering-and-foam)

![ESP32-CAM PIR: Solar Off-Grid Motion Camera](https://shillehtek.com/cdn/shop/articles/blog-thumbnail-627385172255_df47048a-5438-40f5-a01f-c3d4a3f3ad6a.png?v=1781362719)

## Examples in this folder

- [`esp32/`](./esp32/) — 1 sample(s)

---
_Generated from [https://shillehtek.com/blogs/news/esp32-cam-pir-solar-off-grid-motion-camera](https://shillehtek.com/blogs/news/esp32-cam-pir-solar-off-grid-motion-camera). Last verified: see commit history._
