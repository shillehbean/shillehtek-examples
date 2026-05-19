# Node.js example using the serialport package to open the USB serial device, write the ON command, wait 2 seconds, then write the OFF command and close the port.
#
# Buy this module: https://shillehtek.com/products/usb-control-module-1-channel-5v-relay-module-no-driver-needed
# Full manual: https://shillehtek.com/blogs/shillehtek-product-manuals/usb-control-module-1-channel-5v-relay-module-no-driver-needed-manual
# More examples: https://github.com/shillehtek/examples
#

// npm install serialport
const { SerialPort } = require('serialport');

const port = new SerialPort({
  path: '/dev/ttyUSB0',  // change to your port
  baudRate: 9600,
});

const ON  = Buffer.from([0xA0, 0x01, 0x01, 0xA2]);
const OFF = Buffer.from([0xA0, 0x01, 0x00, 0xA1]);

port.on('open', () => {
  port.write(ON);
  console.log('Relay ON');

  setTimeout(() => {
    port.write(OFF);
    console.log('Relay OFF');
    port.close();
  }, 2000);
});
