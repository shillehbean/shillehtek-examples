# Python3 script for Raspberry Pi using spidev and gpiozero to communicate with the ADS1256, wait for DRDY, read all eight single-ended channels, and convert readings to voltages.
#
# Buy this module: https://shillehtek.com/products/ads1256-adc-spi-24-bit-8-channel-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1256-adc-spi-24-bit-8-channel-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

#!/usr/bin/env python3
# ADS1256 24-bit ADC on Raspberry Pi - read all eight inputs as single-ended voltages
# Enable SPI first: sudo raspi-config, Interface Options, SPI
# Wiring: 5V = pin 2, GND = pin 6, SCLK = GPIO 11, DIN = GPIO 10, DOUT = GPIO 9,
#         CS = GPIO 8 (CE0), DRDY = GPIO 17, PDWN = 3.3 V (pin 1)
import time
import spidev
from gpiozero import DigitalInputDevice

VREF = 2.5                      # on-board reference voltage

CMD_WAKEUP, CMD_RDATA, CMD_SDATAC = 0x00, 0x01, 0x0F
CMD_RREG, CMD_WREG = 0x10, 0x50
CMD_SELFCAL, CMD_SYNC, CMD_RESET = 0xF0, 0xFC, 0xFE
REG_STATUS, REG_MUX, REG_ADCON, REG_DRATE = 0x00, 0x01, 0x02, 0x03

drdy = DigitalInputDevice(17)
spi = spidev.SpiDev()
spi.open(0, 0)                  # bus 0, chip select CE0
spi.mode = 1
spi.max_speed_hz = 40000        # a slow clock gives the chip its 6.5 us reply delay


def wait_drdy(timeout=1.0):
    """Wait until DRDY goes low. Returns False if nothing happens in time."""
    end = time.monotonic() + timeout
    while drdy.value == 1:
        if time.monotonic() > end:
            return False
    return True


def write_register(reg, value):
    spi.xfer2([CMD_WREG | reg, 0x00, value])


def read_register(reg):
    return spi.xfer2([CMD_RREG | reg, 0x00, 0x00])[2]


def read_volts(channel):
    """Select AIN<channel> against ground and return the settled voltage."""
    write_register(REG_MUX, (channel << 4) | 0x08)     # positive = AINx, negative = AINCOM
    spi.xfer2([CMD_SYNC, CMD_WAKEUP])                  # restart the filter on the new input
    time.sleep(0.012)                                  # one full conversion at 100 samples per second
    wait_drdy()
    reply = spi.xfer2([CMD_RDATA, 0x00, 0x00, 0x00])
    code = (reply[1] << 16) | (reply[2] << 8) | reply[3]
    if code & 0x800000:
        code -= 0x1000000                              # 24-bit two's complement to signed
    return code * (2 * VREF) / 8388607                 # gain 1: full scale = +/-5 V


spi.xfer2([CMD_RESET])
time.sleep(0.01)
spi.xfer2([CMD_SDATAC])
chip_id = read_register(REG_STATUS) >> 4
if chip_id != 3:
    raise SystemExit(f"ADS1256 not found (ID {chip_id}) - check wiring, 5 V power and PDWN")

write_register(REG_ADCON, 0x00)     # gain 1, clock output off
write_register(REG_DRATE, 0x82)     # 100 samples per second
spi.xfer2([CMD_SELFCAL])            # calibrate for these settings
time.sleep(0.1)
wait_drdy()

try:
    while True:
        for channel in range(8):
            print(f"AIN{channel}: {read_volts(channel):9.5f} V")
        print()
        time.sleep(1)
except KeyboardInterrupt:
    spi.close()
