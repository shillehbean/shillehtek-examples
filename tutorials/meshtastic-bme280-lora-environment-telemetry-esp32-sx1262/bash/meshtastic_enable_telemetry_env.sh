# Enable environment telemetry, set the environment telemetry update interval, and enable the environment telemetry screen on the device.
#
# Full tutorial: https://shillehtek.com/blogs/news/meshtastic-bme280-lora-environment-telemetry-esp32-sx1262
# Parts used: https://shillehtek.com/products/bme280-pre-soldered-atmospheric-temperature-pressure-and-humidity-sensor
#             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
#             https://shillehtek.com/products/shillehtek-400-point-breadboard
# More examples: https://github.com/shillehbean/shillehtek-examples
#

meshtastic --port /dev/cu.usbserial-3 --set telemetry.environment_measurement_enabled true
meshtastic --port /dev/cu.usbserial-3 --set telemetry.environment_update_interval 60
meshtastic --port /dev/cu.usbserial-3 --set telemetry.environment_screen_enabled true
