// Node-RED function node that stores incoming sensor payload values (temp and pressure) into flow context for later retrieval.
//
// Full tutorial: https://shillehtek.com/blogs/news/node-red-telegram-sensor-status
// Parts used: https://shillehtek.com/products/shillehtek-bmp180-pre-soldered
// More examples: https://github.com/shillehbean/shillehtek-examples
//

flow.set("latestTemp", msg.payload.temp);
flow.set("latestPressure", msg.payload.pressure);
return msg;
