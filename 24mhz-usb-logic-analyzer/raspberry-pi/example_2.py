# Install PulseView and the fx2lafw firmware driver on Linux/macOS/Windows and connect the analyzer in PulseView, then set sample rate and add protocol decoders.
#
# Buy this module: https://shillehtek.com/products/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/24mhz-8-channel-usb-logic-analyzer-digital-debugger-for-arduino-manual
# More examples: https://github.com/shillehtek/examples
#

# Linux:
sudo apt install pulseview sigrok-firmware-fx2lafw

# macOS (Homebrew):
brew install pulseview sigrok-firmware-fx2lafw

# Windows: download installer from sigrok.org

# Plug in the analyzer.
# Open PulseView -> Connect to Device -> "fx2lafw" driver ->
#   "saleae-logic" or "Cypress" -> Scan -> Select device.
# Set sample rate to 8 or 16 MS/s for typical buses.
# Add decoders by clicking the green "Add protocol decoder" icon.
