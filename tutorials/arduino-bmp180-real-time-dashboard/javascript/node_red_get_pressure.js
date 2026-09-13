// Node-RED function node code that extracts the pressure field from an incoming message payload and returns it as the new payload.
//
// Full tutorial: https://shillehtek.com/blogs/news/arduino-bmp180-real-time-dashboard
// Parts used: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
//             https://shillehtek.com/products/shillehtek-120pcs-multicolored-dupont-wire
//             https://shillehtek.com/products/shillehtek-120pcs-10cm-multicolored-jumper-wire
// More examples: https://github.com/shillehbean/shillehtek-examples
//

return { payload: msg.payload.pressure };
