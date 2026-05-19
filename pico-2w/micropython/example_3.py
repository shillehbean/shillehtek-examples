# Perform a simple HTTP GET request with urequests in MicroPython and print the response status and body.
#
# Buy this module: https://shillehtek.com/products/raspberry-pi-pico-2w-presoldered-headers
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/raspberry-pi-pico-2w-presoldered-headers-manual
# More examples: https://github.com/shillehtek/examples
#

# Raspberry Pi Pico 2W - Simple HTTP GET request
# Make sure you've already connected to WiFi before running this.

import urequests

response = urequests.get("https://httpbin.org/get")
print("Status:", response.status_code)
print("Body:", response.text)
response.close()
