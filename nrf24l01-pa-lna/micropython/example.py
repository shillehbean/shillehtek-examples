# MicroPython example for Raspberry Pi Pico that configures SPI and the nRF24L01 driver, sets power/speed for long range, sends a packed integer on the TX pipe, and runs a receive loop to unpack incoming integers.
#
# Buy this module: https://shillehtek.com/products/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/nrf24l01-pa-lna-wireless-transceiver-module-antenna-1100m-range-manual
# More examples: https://github.com/shillehtek/examples
#

# NRF24L01+ on Pico - MicroPython
# Use micropython-mrequests or peterhinch's nrf24l01 driver

from machine import Pin, SPI
import nrf24l01
import struct, time

spi = SPI(0, baudrate=4000000, polarity=0, phase=0,
          sck=Pin(2), mosi=Pin(3), miso=Pin(4))
nrf = nrf24l01.NRF24L01(spi, cs=Pin(5), ce=Pin(6), payload_size=8)
nrf.set_channel(76)
nrf.set_power_speed(nrf24l01.POWER_3, nrf24l01.SPEED_250K)

# TX:
nrf.open_tx_pipe(b'NODE1')
nrf.send(struct.pack('i', 1234))

# RX:
nrf.open_rx_pipe(0, b'NODE1')
nrf.start_listening()
while True:
    if nrf.any():
        data = nrf.recv()
        print('Got:', struct.unpack('i', data))
    time.sleep_ms(20)
