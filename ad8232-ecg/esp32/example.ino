// Reads the AD8232 output using an ESP32 ADC in MicroPython with proper attenuation and width, monitors LO+ and LO- for leads-off, and prints ECG samples at ~200 Hz.
//
// Buy this module: https://shillehtek.com/products/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit
// Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ad8232-ecg-module-heart-rate-ecg-monitoring-sensor-kit-manual
// More examples: https://github.com/shillehtek/examples
//

# AD8232 ECG Module - ESP32 MicroPython Example
# OUTPUT -> GPIO 34 (ADC1_CH6), LO+ -> GPIO 33, LO- -> GPIO 32

from machine import ADC, Pin
import time

ecg = ADC(Pin(34))
ecg.atten(ADC.ATTN_11DB)      # read full 0 - 3.3V range
ecg.width(ADC.WIDTH_12BIT)    # 0 - 4095

lo_plus  = Pin(33, Pin.IN)
lo_minus = Pin(32, Pin.IN)

print("AD8232 ECG Demo")

while True:
    if lo_plus.value() or lo_minus.value():
        print(0)               # leads off
    else:
        print(ecg.read())      # 0 - 4095
    time.sleep_ms(5)           # ~200 Hz
