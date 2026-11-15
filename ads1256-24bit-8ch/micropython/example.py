# MicroPython example for Raspberry Pi Pico (RP2040) that uses machine.SPI to send commands to the ADS1256, wait for DRDY, and read all eight inputs as single-ended voltages.
#
# Buy this module: https://shillehtek.com/products/ads1256-adc-spi-24-bit-8-channel-module
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/ads1256-adc-spi-24-bit-8-channel-module-manual
# More examples: https://github.com/shillehbean/shillehtek-examples
#

# ADS1256 24-bit ADC on Raspberry Pi Pico (MicroPython) - read all eight inputs
# Wiring: 5V = VBUS, GND = GND, SCLK = GP18, DIN = GP19, DOUT = GP16, CS = GP17,
#         DRDY = GP20, PDWN = 3V3(OUT)
from machine import SPI, Pin
import time

VREF = 2.5                      # on-board reference voltage

CMD_WAKEUP, CMD_RDATA, CMD_SDATAC = 0x00, 0x01, 0x0F
CMD_RREG, CMD_WREG = 0x10, 0x50
CMD_SELFCAL, CMD_SYNC, CMD_RESET = 0xF0, 0xFC, 0xFE
REG_STATUS, REG_MUX, REG_ADCON, REG_DRATE = 0x00, 0x01, 0x02, 0x03

spi = SPI(0, baudrate=1000000, polarity=0, phase=1, sck=Pin(18), mosi=Pin(19), miso=Pin(16))
cs = Pin(17, Pin.OUT, value=1)
drdy = Pin(20, Pin.IN)


def wait_drdy(timeout_ms=1000):
    # Wait until DRDY goes low. Returns False if nothing happens in time.
    start = time.ticks_ms()
    while drdy.value() == 1:
        if time.ticks_diff(time.ticks_ms(), start) > timeout_ms:
            return False
    return True


def command(*data):
    cs.value(0)
    spi.write(bytes(data))
    cs.value(1)


def read_after(data, count):
    # Send a command, give the chip its 6.5 us reply delay, then read count bytes
    cs.value(0)
    spi.write(bytes(data))
    time.sleep_us(10)
    reply = spi.read(count, 0x00)
    cs.value(1)
    return reply


def read_volts(channel):
    # Select AIN<channel> against ground and return the settled voltage
    command(CMD_WREG | REG_MUX, 0x00, (channel << 4) | 0x08)    # positive = AINx, negative = AINCOM
    cs.value(0)
    spi.write(bytes([CMD_SYNC]))
    time.sleep_us(5)
    spi.write(bytes([CMD_WAKEUP]))          # restart the filter on the new input
    cs.value(1)
    time.sleep_ms(12)                       # one full conversion at 100 samples per second
    wait_drdy()
    raw = read_after([CMD_RDATA], 3)
    code = (raw[0] << 16) | (raw[1] << 8) | raw[2]
    if code & 0x800000:
        code -= 0x1000000                   # 24-bit two's complement to signed
    return code * (2 * VREF) / 8388607      # gain 1: full scale = +/-5 V


command(CMD_RESET)
time.sleep_ms(10)
command(CMD_SDATAC)
chip_id = read_after([CMD_RREG | REG_STATUS, 0x00], 1)[0] >> 4
if chip_id != 3:
    raise RuntimeError("ADS1256 not found (ID {}) - check wiring, 5 V power and PDWN".format(chip_id))

command(CMD_WREG | REG_ADCON, 0x00, 0x00)   # gain 1, clock output off
command(CMD_WREG | REG_DRATE, 0x00, 0x82)   # 100 samples per second
command(CMD_SELFCAL)                        # calibrate for these settings
time.sleep_ms(100)
wait_drdy()

while True:
    for channel in range(8):
        print("AIN{}: {:9.5f} V".format(channel, read_volts(channel)))
    print()
    time.sleep(1)
